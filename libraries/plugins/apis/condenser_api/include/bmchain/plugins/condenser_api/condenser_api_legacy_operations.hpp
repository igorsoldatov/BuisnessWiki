#include <bmchain/protocol/operations.hpp>
#include <bmchain/protocol>
#include <bmchain/chain/witness_objects.hpp>

#include <bmchain/plugins/condenser_api/condenser_api_legacy_asset.hpp>

namespace bmchain { namespace plugins { namespace condenser_api {

   template< typename T >
   struct convert_to_legacy_static_variant
   {
      convert_to_legacy_static_variant( T& l_sv ) :
         legacy_sv( l_sv ) {}

      T& legacy_sv;

      typedef void result_type;

      template< typename V >
      void operator()( const V& v ) const
      {
         legacy_sv = v;
      }
   };

   typedef static_variant<
            protocol::comment_payout_beneficiaries
   #ifdef STEEM_ENABLE_SMT
            ,protocol::allowed_vote_assets
   #endif
         > legacy_comment_options_extensions;

   typedef vector< legacy_comment_options_extensions > legacy_comment_options_extensions_type;

   typedef static_variant<
            protocol::pow2,
            protocol::equihash_pow
         > legacy_pow2_work;

   using namespace steem::protocol;

   typedef escrow_approve_operation               legacy_escrow_approve_operation;
   typedef escrow_dispute_operation               legacy_escrow_dispute_operation;
   typedef set_withdraw_vesting_route_operation   legacy_set_withdraw_vesting_route_operation;
   typedef witness_set_properties_operation       legacy_witness_set_properties_operation;
   typedef pow_operation                          legacy_pow_operation;
   typedef report_over_production_operation       legacy_report_over_production_operation;
   typedef request_account_recovery_operation     legacy_request_account_recovery_operation;
   typedef recover_account_operation              legacy_recover_account_operation;
   typedef reset_account_operation                legacy_reset_account_operation;
   typedef set_reset_account_operation            legacy_set_reset_account_operation;
   typedef change_recovery_account_operation      legacy_change_recovery_account_operation;
   typedef cancel_transfer_from_savings_operation legacy_cancel_transfer_from_savings_operation;
   typedef decline_voting_rights_operation        legacy_decline_voting_rights_operation;
   typedef shutdown_witness_operation             legacy_shutdown_witness_operation;
   typedef hardfork_operation                     legacy_hardfork_operation;
   typedef comment_payout_update_operation        legacy_comment_payout_update_operation;

   struct legacy_price
   {
      legacy_price() {}
      legacy_price( const protocol::price& p ) :
         base( legacy_asset::from_asset( p.base ) ),
         quote( legacy_asset::from_asset( p.quote ) )
      {}

      operator price()const { return price( base, quote ); }

      legacy_asset base;
      legacy_asset quote;
   };

   struct api_chain_properties
   {
      api_chain_properties() {}
      api_chain_properties( const chain::chain_properties& c ) :
         account_creation_fee( legacy_asset::from_asset( c.account_creation_fee ) ),
         maximum_block_size( c.maximum_block_size ),
         sbd_interest_rate( c.sbd_interest_rate ),
         account_subsidy_budget( c.account_subsidy_budget ),
         account_subsidy_decay( c.account_subsidy_decay )
      {}

      operator legacy_chain_properties() const
      {
         legacy_chain_properties props;
         props.account_creation_fee = legacy_steem_asset::from_asset( asset( account_creation_fee ) );
         props.maximum_block_size = maximum_block_size;
         props.sbd_interest_rate = sbd_interest_rate;
         return props;
      }

      legacy_asset   account_creation_fee;
      uint32_t       maximum_block_size = STEEM_MIN_BLOCK_SIZE_LIMIT * 2;
      uint16_t       sbd_interest_rate = STEEM_DEFAULT_SBD_INTEREST_RATE;
      int32_t        account_subsidy_budget = STEEM_DEFAULT_ACCOUNT_SUBSIDY_BUDGET;
      uint32_t       account_subsidy_decay = STEEM_DEFAULT_ACCOUNT_SUBSIDY_DECAY;
   };

   struct legacy_account_create_operation
   {
      legacy_account_create_operation() {}
      legacy_account_create_operation( const account_create_operation& op ) :
         fee( legacy_asset::from_asset( op.fee ) ),
         creator( op.creator ),
         new_account_name( op.new_account_name ),
         owner( op.owner ),
         active( op.active ),
         posting( op.posting ),
         memo_key( op.memo_key ),
         json_metadata( op.json_metadata )
      {}

      operator account_create_operation()const
      {
         account_create_operation op;
         op.fee = fee;
         op.creator = creator;
         op.new_account_name = new_account_name;
         op.owner = owner;
         op.active = active;
         op.posting = posting;
         op.memo_key = memo_key;
         op.json_metadata = json_metadata;
         return op;
      }

      legacy_asset      fee;
      account_name_type creator;
      account_name_type new_account_name;
      authority         owner;
      authority         active;
      authority         posting;
      public_key_type   memo_key;
      string            json_metadata;
   };

   struct legacy_account_create_with_delegation_operation
   {
      legacy_account_create_with_delegation_operation() {}
      legacy_account_create_with_delegation_operation( const account_create_with_delegation_operation op ) :
         fee( legacy_asset::from_asset( op.fee ) ),
         delegation( legacy_asset::from_asset( op.delegation ) ),
         creator( op.creator ),
         new_account_name( op.new_account_name ),
         owner( op.owner ),
         active( op.active ),
         posting( op.posting ),
         memo_key( op.memo_key ),
         json_metadata( op.json_metadata )
      {
         extensions.insert( op.extensions.begin(), op.extensions.end() );
      }

      operator account_create_with_delegation_operation()const
      {
         account_create_with_delegation_operation op;
         op.fee = fee;
         op.delegation = delegation;
         op.creator = creator;
         op.new_account_name = new_account_name;
         op.owner = owner;
         op.active = active;
         op.posting = posting;
         op.memo_key = memo_key;
         op.json_metadata = json_metadata;
         op.extensions.insert( extensions.begin(), extensions.end() );
         return op;
      }

      legacy_asset      fee;
      legacy_asset      delegation;
      account_name_type creator;
      account_name_type new_account_name;
      authority         owner;
      authority         active;
      authority         posting;
      public_key_type   memo_key;
      string            json_metadata;

      extensions_type   extensions;
   };



} } } // steem::plugins::condenser_api


