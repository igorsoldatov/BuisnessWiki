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

// Highly optimized implementation of Damm algorithm
// https://en.wikipedia.org/wiki/Damm_algorithm
uint8_t damm_checksum_8digit(uint32_t value)
{
            FC_ASSERT( value < 100000000 );

            const uint8_t t[] = {
                    0, 30, 10, 70, 50, 90, 80, 60, 40, 20,
                    70,  0, 90, 20, 10, 50, 40, 80, 60, 30,
                    40, 20,  0, 60, 80, 70, 10, 30, 50, 90,
                    10, 70, 50,  0, 90, 80, 30, 40, 20, 60,
                    60, 10, 20, 30,  0, 40, 50, 90, 70, 80,
                    30, 60, 70, 40, 20,  0, 90, 50, 80, 10,
                    50, 80, 60, 90, 70, 20,  0, 10, 30, 40,
                    80, 90, 40, 50, 30, 60, 20,  0, 10, 70,
                    90, 40, 30, 80, 60, 10, 70, 20,  0, 50,
                    20, 50, 80, 10, 40, 30, 60, 70, 90, 0
            };

            uint32_t q0 = value/10;
            uint32_t d0 = value%10;
            uint32_t q1 = q0/10;
            uint32_t d1 = q0%10;
            uint32_t q2 = q1/10;
            uint32_t d2 = q1%10;
            uint32_t q3 = q2/10;
            uint32_t d3 = q2%10;
            uint32_t q4 = q3/10;
            uint32_t d4 = q3%10;
            uint32_t q5 = q4/10;
            uint32_t d5 = q4%10;
            uint32_t d6 = q5%10;
            uint32_t d7 = q5/10;

            uint8_t x = t[d7];
            x = t[x+d6];
            x = t[x+d5];
            x = t[x+d4];
            x = t[x+d3];
            x = t[x+d2];
            x = t[x+d1];
            x = t[x+d0];
            return x/10;
        }

uint32_t asset_symbol_type::asset_num_from_nai( uint32_t nai, uint8_t decimal_places )
{
            // Can be replaced with some clever bitshifting
            uint32_t nai_check_digit = nai % 10;
            uint32_t nai_data_digits = nai / 10;

            FC_ASSERT( (nai_data_digits >= SMT_MIN_NAI) & (nai_data_digits <= SMT_MAX_NAI), "NAI out of range" );
            FC_ASSERT( nai_check_digit == damm_checksum_8digit(nai_data_digits), "Invalid check digit" );

            switch( nai_data_digits )
            {
                case STEEM_NAI_STEEM:
                    FC_ASSERT( decimal_places == STEEM_PRECISION_STEEM );
                    return STEEM_ASSET_NUM_STEEM;
                case STEEM_NAI_SBD:
                    FC_ASSERT( decimal_places == STEEM_PRECISION_SBD );
                    return STEEM_ASSET_NUM_SBD;
                case STEEM_NAI_VESTS:
                    FC_ASSERT( decimal_places == STEEM_PRECISION_VESTS );
                    return STEEM_ASSET_NUM_VESTS;
                default:
                    FC_ASSERT( decimal_places <= STEEM_ASSET_MAX_DECIMALS, "Invalid decimal_places" );
                    return (nai_data_digits << 5) | 0x10 | decimal_places;
            }
        }


} } // bmchain::protocol


