#include <bmchain/protocol/new_asset.hpp>

#include <fc/io/json.hpp>

#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp>

/*

The bounds on asset serialization are as follows:

index : field
0     : decimals
1..6  : symbol
   7  : \0
*/

namespace bmchain { namespace protocol {

        std::string asset_symbol_type::to_string()const
        {
            return fc::json::to_string( fc::variant( *this ) );
        }

        asset_symbol_type asset_symbol_type::from_string( const std::string& str )
        {
            return fc::json::from_string( str ).as< asset_symbol_type >();
        }

        void asset_symbol_type::to_nai_string( char* buf )const
        {
            static_assert( STEEM_ASSET_SYMBOL_NAI_STRING_LENGTH >= 12, "This code will overflow a short buffer" );
            uint32_t x = to_nai();
            buf[11] = '\0';
            buf[10] = ((x%10)+'0');  x /= 10;
            buf[ 9] = ((x%10)+'0');  x /= 10;
            buf[ 8] = ((x%10)+'0');  x /= 10;
            buf[ 7] = ((x%10)+'0');  x /= 10;
            buf[ 6] = ((x%10)+'0');  x /= 10;
            buf[ 5] = ((x%10)+'0');  x /= 10;
            buf[ 4] = ((x%10)+'0');  x /= 10;
            buf[ 3] = ((x%10)+'0');  x /= 10;
            buf[ 2] = ((x   )+'0');
            buf[ 1] = '@';
            buf[ 0] = '@';
        }

        asset_symbol_type asset_symbol_type::from_nai_string( const char* p, uint8_t decimal_places )
        {
            // \s*
            while( true )
            {
                switch( *p )
                {
                    case ' ':  case '\t':  case '\n':  case '\r':
                        ++p;
                        continue;
                    default:
                        break;
                }
                break;
            }

            // [A-Z]{1,6}
            uint32_t asset_num = 0;
            switch( *p )
            {
                case '@':
                {
                    ++p;
                    FC_ASSERT( (*p) == '@', "Cannot parse asset symbol" );
                    ++p;

                    uint64_t nai = 0;
                    int digit_count = 0;
                    while( true )
                    {
                        switch( *p )
                        {
                            case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                            {
                                uint64_t new_nai = nai*10 + ((*p) - '0');
                                FC_ASSERT( new_nai >= nai, "Cannot parse asset amount" ); // This is failing for system assets
                                FC_ASSERT( new_nai <= SMT_MAX_NAI, "Cannot parse asset amount" );
                                nai = new_nai;
                                ++p;
                                ++digit_count;
                                continue;
                            }
                            default:
                                break;
                        }
                        break;
                    }
                    FC_ASSERT( digit_count == 9 );
                    asset_num = asset_num_from_nai( nai, uint8_t( decimal_places ) );
                    break;
                }
                default:
                    FC_ASSERT( false, "Cannot parse asset symbol" );
            }

            // \s*\0
            while( true )
            {
                switch( *p )
                {
                    case ' ':  case '\t':  case '\n':  case '\r':
                        ++p;
                        continue;
                    case '\0':
                        break;
                    default:
                        FC_ASSERT( false, "Cannot parse asset symbol" );
                }
                break;
            }

            asset_symbol_type sym;
            sym.asset_num = asset_num;
            return sym;
        }

    } } // steem::protocol


