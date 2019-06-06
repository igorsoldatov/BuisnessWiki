#pragma once

#include <bmchain/protocol/types.hpp>
#include <bmchain/protocol/config.hpp>
#include <bmchain/protocol/asset_symbol.hpp>

namespace bmchain { namespace protocol {

   typedef uint64_t asset_symbol_type;

   struct asset
   {
      asset( share_type a = 0, asset_symbol_type id = BWC_SYMBOL )
      :amount(a),symbol(id){}

      share_type        amount;
      asset_symbol_type symbol;

      double to_real()const {
         return double(amount.value) / precision();
      }

      uint8_t     decimals()const;
      std::string symbol_name()const;
      int64_t     precision()const;
      void        set_decimals(uint8_t d);

      static asset from_string( const string& from );
      string       to_string()const;

      asset& operator += ( const asset& o )
      {
         FC_ASSERT( symbol == o.symbol );
         amount += o.amount;
         return *this;
      }

      asset& operator -= ( const asset& o )
      {
         FC_ASSERT( symbol == o.symbol );
         amount -= o.amount;
         return *this;
      }
      asset operator -()const { return asset( -amount, symbol ); }

      friend bool operator == ( const asset& a, const asset& b )
      {
         return std::tie( a.symbol, a.amount ) == std::tie( b.symbol, b.amount );
      }
      friend bool operator < ( const asset& a, const asset& b )
      {
         FC_ASSERT( a.symbol == b.symbol );
         return std::tie(a.amount,a.symbol) < std::tie(b.amount,b.symbol);
      }
      friend bool operator <= ( const asset& a, const asset& b )
      {
         return (a == b) || (a < b);
      }

      friend bool operator != ( const asset& a, const asset& b )
      {
         return !(a == b);
      }
      friend bool operator > ( const asset& a, const asset& b )
      {
         return !(a <= b);
      }
      friend bool operator >= ( const asset& a, const asset& b )
      {
         return !(a < b);
      }

      friend asset operator - ( const asset& a, const asset& b )
      {
         FC_ASSERT( a.symbol == b.symbol );
         return asset( a.amount - b.amount, a.symbol );
      }
      friend asset operator + ( const asset& a, const asset& b )
      {
         FC_ASSERT( a.symbol == b.symbol );
         return asset( a.amount + b.amount, a.symbol );
      }

   };

   struct price
   {
      price(const asset& base = asset(), const asset& quote = asset())
         : base(base),quote(quote){}

      asset base;
      asset quote;

      static price max(asset_symbol_type base, asset_symbol_type quote );
      static price min(asset_symbol_type base, asset_symbol_type quote );

      price max()const { return price::max( base.symbol, quote.symbol ); }
      price min()const { return price::min( base.symbol, quote.symbol ); }

      double to_real()const { return base.to_real() / quote.to_real(); }

      bool is_null()const;
      void validate()const;
   };

   price operator / ( const asset& base, const asset& quote );
   inline price operator~( const price& p ) { return price{p.quote,p.base}; }

   bool  operator <  ( const asset& a, const asset& b );
   bool  operator <= ( const asset& a, const asset& b );
   bool  operator <  ( const price& a, const price& b );
   bool  operator <= ( const price& a, const price& b );
   bool  operator >  ( const price& a, const price& b );
   bool  operator >= ( const price& a, const price& b );
   bool  operator == ( const price& a, const price& b );
   bool  operator != ( const price& a, const price& b );
   asset operator *  ( const asset& a, const price& b );

   struct nn_asset
   {
      nn_asset( const nn_asset& nn_asset, asset_smbl_type id )
      :amount( nn_asset.amount ),symbol(id){}

      nn_asset( share_type a, asset_smbl_type id )
         :amount(a),symbol(id){}

      nn_asset()
         :amount(0),symbol(BWC_SYMBOL_NN){}

      share_type        amount;
      asset_smbl_type symbol;

      void validate()const;

      nn_asset& operator += ( const nn_asset& o )
      {
         FC_ASSERT( symbol == o.symbol );
         amount += o.amount;
         return *this;
      }

      nn_asset& operator -= ( const nn_asset& o )
      {
         FC_ASSERT( symbol == o.symbol );
         amount -= o.amount;
         return *this;
      }
      nn_asset operator -()const { return nn_asset( -amount, symbol ); }

      friend bool operator == ( const nn_asset& a, const nn_asset& b )
      {
         return std::tie( a.symbol, a.amount ) == std::tie( b.symbol, b.amount );
      }
      friend bool operator < ( const nn_asset& a, const nn_asset& b )
      {
         FC_ASSERT( a.symbol == b.symbol );
         return a.amount < b.amount;
      }

      friend bool operator <= ( const nn_asset& a, const nn_asset& b )
      {
         FC_ASSERT( a.symbol == b.symbol );
         return a.amount <= b.amount;
      }

      friend bool operator != ( const nn_asset& a, const nn_asset& b )
      {
         FC_ASSERT( a.symbol == b.symbol );
         return a.amount != b.amount;
      }

      friend bool operator > ( const nn_asset& a, const nn_asset& b )
      {
         FC_ASSERT( a.symbol == b.symbol );
         return a.amount > b.amount;
      }

      friend bool operator >= ( const nn_asset& a, const nn_asset& b )
      {
         FC_ASSERT( a.symbol == b.symbol );
         return a.amount >= b.amount;
      }

      friend nn_asset operator - ( const nn_asset& a, const nn_asset& b )
      {
         FC_ASSERT( a.symbol == b.symbol );
         return nn_asset( a.amount - b.amount, a.symbol );
      }
      friend nn_asset operator + ( const nn_asset& a, const nn_asset& b )
      {
         FC_ASSERT( a.symbol == b.symbol );
         return nn_asset( a.amount + b.amount, a.symbol );
      }

      friend nn_asset operator * ( const nn_asset& a, const nn_asset& b )
      {
         FC_ASSERT( a.symbol == b.symbol );
         return nn_asset( a.amount * b.amount, a.symbol );
      }
   };

   /** Represents quotation of the relative value of asset against another asset.
       Similar to 'currency pair' used to determine value of currencies.

       For example:
       1 EUR / 1.25 USD where:
       1 EUR is an asset specified as a base
       1.25 USD us an asset specified as a qute

       can determine value of EUR against USD.
   */
   struct nn_price
   {
      /** Even non-single argument, lets make it an explicit one to avoid implicit calls for
          initialization lists.

          \param base  - represents a value of the price object to be expressed relatively to quote
                         asset. Cannot have amount == 0 if you want to build valid price.
          \param quote - represents an relative asset. Cannot have amount == 0, otherwise
                         asertion fail.

        Both base and quote shall have different symbol defined, since it also results in
        creation of invalid price object. \see validate() method.
      */
      explicit nn_price(const nn_asset& base, const nn_asset& quote) : base(base),quote(quote)
      {
          /// Call validate to verify passed arguments. \warning It throws on error.
          validate();
      }

      /** Default constructor is needed because of fc::variant::as method requirements.
      */
      nn_price() = default;

      nn_asset base;
      nn_asset quote;

      static nn_price max(asset_smbl_type base, asset_smbl_type quote );
      static nn_price min(asset_smbl_type base, asset_smbl_type quote );

      nn_price max()const { return nn_price::max( base.symbol, quote.symbol ); }
      nn_price min()const { return nn_price::min( base.symbol, quote.symbol ); }

      bool is_null()const;
      void validate()const;

   }; /// price

   nn_price operator / ( const nn_asset& base, const nn_asset& quote );
   inline nn_price operator~( const nn_price& p ) { return nn_price{p.quote,p.base}; }

   bool  operator <  ( const nn_asset& a, const nn_asset& b );
   bool  operator <= ( const nn_asset& a, const nn_asset& b );
   bool  operator <  ( const nn_price& a, const nn_price& b );
   bool  operator <= ( const nn_price& a, const nn_price& b );
   bool  operator >  ( const nn_price& a, const nn_price& b );
   bool  operator >= ( const nn_price& a, const nn_price& b );
   bool  operator == ( const nn_price& a, const nn_price& b );
   bool  operator != ( const nn_price& a, const nn_price& b );
   nn_asset operator *  ( const nn_asset& a, const nn_price& b );

} } // bmchain::protocol

namespace fc {
    inline void to_variant( const bmchain::protocol::asset& var,  fc::variant& vo ) { vo = var.to_string(); }
    inline void from_variant( const fc::variant& var,  bmchain::protocol::asset& vo ) { vo = bmchain::protocol::asset::from_string( var.as_string() ); }

    void to_variant( const bmchain::protocol::nn_asset& var,  fc::variant& vo );
    void from_variant( const fc::variant& var,  bmchain::protocol::nn_asset& vo );
}

FC_REFLECT( bmchain::protocol::asset, (amount)(symbol) )
FC_REFLECT( bmchain::protocol::price, (base)(quote) )

FC_REFLECT( bmchain::protocol::nn_asset, (amount)(symbol) )
FC_REFLECT( bmchain::protocol::nn_price, (base)(quote) )