#include <bmchain/protocol/get_config.hpp>
#include <bmchain/protocol/config.hpp>
#include <bmchain/protocol/asset.hpp>
#include <bmchain/protocol/types.hpp>
#include <bmchain/protocol/version.hpp>
#include <graphene/utilities/key_conversion.hpp>

namespace bmchain { namespace protocol {

fc::variant_object get_config()
{
   fc::mutable_variant_object result;

#ifdef IS_TEST_NET
   result[ "IS_TEST_NET" ] = true;
#else
   result[ "IS_TEST_NET" ] = false;
#endif

   result["BWC_SYMBOL"] = BWC_SYMBOL;
   result["BMCHAIN_100_PERCENT"] = BMCHAIN_100_PERCENT;
   result["BMCHAIN_1_PERCENT"] = BMCHAIN_1_PERCENT;
   result["BMCHAIN_1_TENTH_PERCENT"] = BMCHAIN_1_TENTH_PERCENT;
   result["BMCHAIN_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD"] = BMCHAIN_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD;
   result["BMCHAIN_ACTIVE_CHALLENGE_COOLDOWN"] = BMCHAIN_ACTIVE_CHALLENGE_COOLDOWN;
   result["BMCHAIN_ACTIVE_CHALLENGE_FEE"] = BMCHAIN_ACTIVE_CHALLENGE_FEE;
   result["BMCHAIN_ADDRESS_PREFIX"] = BMCHAIN_ADDRESS_PREFIX;
   result["BMCHAIN_APR_PERCENT_MULTIPLY_PER_BLOCK"] = BMCHAIN_APR_PERCENT_MULTIPLY_PER_BLOCK;
   result["BMCHAIN_APR_PERCENT_MULTIPLY_PER_HOUR"] = BMCHAIN_APR_PERCENT_MULTIPLY_PER_HOUR;
   result["BMCHAIN_APR_PERCENT_MULTIPLY_PER_ROUND"] = BMCHAIN_APR_PERCENT_MULTIPLY_PER_ROUND;
   result["BMCHAIN_APR_PERCENT_SHIFT_PER_BLOCK"] = BMCHAIN_APR_PERCENT_SHIFT_PER_BLOCK;
   result["BMCHAIN_APR_PERCENT_SHIFT_PER_HOUR"] = BMCHAIN_APR_PERCENT_SHIFT_PER_HOUR;
   result["BMCHAIN_APR_PERCENT_SHIFT_PER_ROUND"] = BMCHAIN_APR_PERCENT_SHIFT_PER_ROUND;
   result["BMCHAIN_BANDWIDTH_AVERAGE_WINDOW_SECONDS"] = BMCHAIN_BANDWIDTH_AVERAGE_WINDOW_SECONDS;
   result["BMCHAIN_BANDWIDTH_PRECISION"] = BMCHAIN_BANDWIDTH_PRECISION;
   result["BMCHAIN_BLOCKCHAIN_PRECISION"] = BMCHAIN_BLOCKCHAIN_PRECISION;
   result["BMCHAIN_BLOCKCHAIN_PRECISION_DIGITS"] = BMCHAIN_BLOCKCHAIN_PRECISION_DIGITS;
   result["BMCHAIN_BLOCKCHAIN_HARDFORK_VERSION"] = BMCHAIN_BLOCKCHAIN_HARDFORK_VERSION;
   result["BMCHAIN_BLOCKCHAIN_VERSION"] = BMCHAIN_BLOCKCHAIN_VERSION;
   result["BMCHAIN_BLOCK_INTERVAL"] = BMCHAIN_BLOCK_INTERVAL;
   result["BMCHAIN_BLOCKS_PER_DAY"] = BMCHAIN_BLOCKS_PER_DAY;
   result["BMCHAIN_START_VESTING_BLOCK"] = BMCHAIN_START_VESTING_BLOCK;
   result["BMCHAIN_BLOCKS_PER_HOUR"] = BMCHAIN_BLOCKS_PER_HOUR;
   result["BMCHAIN_BLOCKS_PER_YEAR"] = BMCHAIN_BLOCKS_PER_YEAR;
   result["BMCHAIN_CASHOUT_WINDOW_SECONDS"] = BMCHAIN_CASHOUT_WINDOW_SECONDS;
   result["BMCHAIN_CHAIN_ID"] = BMCHAIN_CHAIN_ID;
   result["BMCHAIN_COMMENT_REWARD_FUND_NAME"] = BMCHAIN_COMMENT_REWARD_FUND_NAME;
   result["BMCHAIN_CONTENT_APR_PERCENT"] = BMCHAIN_CONTENT_APR_PERCENT;
   result["BMCHAIN_CONTENT_CONSTANT"] = BMCHAIN_CONTENT_CONSTANT;
   result["BMCHAIN_INFLATION_RATE_START_PERCENT"] = BMCHAIN_INFLATION_RATE_START_PERCENT;
   result["BMCHAIN_INFLATION_RATE_STOP_PERCENT"] = BMCHAIN_INFLATION_RATE_STOP_PERCENT;
   result["BMCHAIN_INFLATION_NARROWING_PERIOD"] = BMCHAIN_INFLATION_NARROWING_PERIOD;
   result["BMCHAIN_CONTENT_REWARD_PERCENT"] = BMCHAIN_CONTENT_REWARD_PERCENT;
   result["BMCHAIN_CONTENT_REWARD_PERCENT_NEW"] = BMCHAIN_CONTENT_REWARD_PERCENT_NEW;
   result["BMCHAIN_VESTING_FUND_PERCENT"] = BMCHAIN_VESTING_FUND_PERCENT;
   result["BMCHAIN_CONVERSION_DELAY"] = BMCHAIN_CONVERSION_DELAY;
   result["BMCHAIN_CREATE_ACCOUNT_DELEGATION_RATIO"] = BMCHAIN_CREATE_ACCOUNT_DELEGATION_RATIO;
   result["BMCHAIN_CREATE_ACCOUNT_DELEGATION_TIME"] = BMCHAIN_CREATE_ACCOUNT_DELEGATION_TIME;
   result["BMCHAIN_CREATE_ACCOUNT_WITH_BMT_MODIFIER"] = BMCHAIN_CREATE_ACCOUNT_WITH_BMT_MODIFIER;
   result["BMCHAIN_CURATE_APR_PERCENT"] = BMCHAIN_CURATE_APR_PERCENT;
   result["BMCHAIN_EQUIHASH_K"] = BMCHAIN_EQUIHASH_K;
   result["BMCHAIN_EQUIHASH_N"] = BMCHAIN_EQUIHASH_N;
   result["BMCHAIN_FEED_HISTORY_WINDOW"] = BMCHAIN_FEED_HISTORY_WINDOW;
   result["BMCHAIN_FEED_INTERVAL_BLOCKS"] = BMCHAIN_FEED_INTERVAL_BLOCKS;
   result["BMCHAIN_GENESIS_TIME"] = BMCHAIN_GENESIS_TIME;
   result["BMCHAIN_HARDFORK_REQUIRED_WITNESSES"] = BMCHAIN_HARDFORK_REQUIRED_WITNESSES;
   result["BMCHAIN_INIT_MINER_NAME"] = BMCHAIN_INIT_MINER_NAME;
   result["BMCHAIN_INIT_PUBLIC_KEY_STR"] = BMCHAIN_INIT_PUBLIC_KEY_STR;
#if 0
   // do not expose private key, period.
   // we need this line present but inactivated so CI check for all constants in config.hpp doesn't complain.
   result["BMCHAIN_INIT_PRIVATE_KEY"] = BMCHAIN_INIT_PRIVATE_KEY;
#endif
   result["BMCHAIN_INIT_SUPPLY"] = BMCHAIN_INIT_SUPPLY;
   result["BMCHAIN_INIT_SUPPLY_REP"] = BMCHAIN_INIT_SUPPLY_REP;
   result["BMCHAIN_TRANSFER_REP_BLOCK"] = BMCHAIN_TRANSFER_REP_BLOCK;
   result["BMCHAIN_INIT_TIME"] = BMCHAIN_INIT_TIME;
   result["BMCHAIN_IRREVERSIBLE_THRESHOLD"] = BMCHAIN_IRREVERSIBLE_THRESHOLD;
   result["BMCHAIN_LIQUIDITY_APR_PERCENT"] = BMCHAIN_LIQUIDITY_APR_PERCENT;
   result["BMCHAIN_LIQUIDITY_REWARD_BLOCKS"] = BMCHAIN_LIQUIDITY_REWARD_BLOCKS;
   result["BMCHAIN_LIQUIDITY_REWARD_PERIOD_SEC"] = BMCHAIN_LIQUIDITY_REWARD_PERIOD_SEC;
   result["BMCHAIN_MAX_ACCOUNT_NAME_LENGTH"] = BMCHAIN_MAX_ACCOUNT_NAME_LENGTH;
   result["BMCHAIN_MAX_ACCOUNT_WITNESS_VOTES"] = BMCHAIN_MAX_ACCOUNT_WITNESS_VOTES;
   result["BMCHAIN_MAX_ASSET_WHITELIST_AUTHORITIES"] = BMCHAIN_MAX_ASSET_WHITELIST_AUTHORITIES;
   result["BMCHAIN_MAX_AUTHORITY_MEMBERSHIP"] = BMCHAIN_MAX_AUTHORITY_MEMBERSHIP;
   result["BMCHAIN_MAX_BLOCK_SIZE"] = BMCHAIN_MAX_BLOCK_SIZE;
   result["BMCHAIN_MAX_COMMENT_DEPTH"] = BMCHAIN_MAX_COMMENT_DEPTH;
   result["BMCHAIN_MAX_FEED_AGE_SECONDS"] = BMCHAIN_MAX_FEED_AGE_SECONDS;
   result["BMCHAIN_MAX_INSTANCE_ID"] = BMCHAIN_MAX_INSTANCE_ID;
   result["BMCHAIN_MAX_MEMO_SIZE"] = BMCHAIN_MAX_MEMO_SIZE;
   result["BMCHAIN_MAX_WITNESSES"] = BMCHAIN_MAX_WITNESSES;
   result["BMCHAIN_MAX_MINER_WITNESSES"] = BMCHAIN_MAX_MINER_WITNESSES;
   result["BMCHAIN_MAX_PERMLINK_LENGTH"] = BMCHAIN_MAX_PERMLINK_LENGTH;
   result["BMCHAIN_MAX_PROXY_RECURSION_DEPTH"] = BMCHAIN_MAX_PROXY_RECURSION_DEPTH;
   result["BMCHAIN_VESTING_WITHDRAW_INTERVALS"] = BMCHAIN_VESTING_WITHDRAW_INTERVALS;
   result["BMCHAIN_VESTING_WITHDRAW_INTERVAL_SECONDS"] = BMCHAIN_VESTING_WITHDRAW_INTERVAL_SECONDS;
   result["BMCHAIN_MAX_WITHDRAW_ROUTES"] = BMCHAIN_MAX_WITHDRAW_ROUTES;
   result["BMCHAIN_MAX_RESERVE_RATIO"] = BMCHAIN_MAX_RESERVE_RATIO;
   result["BMCHAIN_MAX_RUNNER_WITNESSES"] = BMCHAIN_MAX_RUNNER_WITNESSES;
   result["BMCHAIN_MAX_SHARE_SUPPLY"] = BMCHAIN_MAX_SHARE_SUPPLY;
   result["BMCHAIN_MAX_SIG_CHECK_DEPTH"] = BMCHAIN_MAX_SIG_CHECK_DEPTH;
   result["BMCHAIN_MAX_TIME_UNTIL_EXPIRATION"] = BMCHAIN_MAX_TIME_UNTIL_EXPIRATION;
   result["BMCHAIN_MAX_TRANSACTION_SIZE"] = BMCHAIN_MAX_TRANSACTION_SIZE;
   result["BMCHAIN_MAX_UNDO_HISTORY"] = BMCHAIN_MAX_UNDO_HISTORY;
   result["BMCHAIN_MAX_URL_LENGTH"] = BMCHAIN_MAX_URL_LENGTH;
   result["BMCHAIN_MAX_VOTE_CHANGES"] = BMCHAIN_MAX_VOTE_CHANGES;
   result["BMCHAIN_MAX_VOTED_WITNESSES"] = BMCHAIN_MAX_VOTED_WITNESSES;
   result["BMCHAIN_MAX_WITNESS_URL_LENGTH"] = BMCHAIN_MAX_WITNESS_URL_LENGTH;
   result["BMCHAIN_MIN_ACCOUNT_CREATION_FEE"] = BMCHAIN_MIN_ACCOUNT_CREATION_FEE;
   result["BMCHAIN_MIN_ACCOUNT_NAME_LENGTH"] = BMCHAIN_MIN_ACCOUNT_NAME_LENGTH;
   result["BMCHAIN_MIN_BLOCK_SIZE"] = BMCHAIN_MIN_BLOCK_SIZE;
   result["BMCHAIN_MIN_BLOCK_SIZE_LIMIT"] = BMCHAIN_MIN_BLOCK_SIZE_LIMIT;
   result["BMCHAIN_MIN_CONTENT_REWARD"] = BMCHAIN_MIN_CONTENT_REWARD;
   result["BMCHAIN_MIN_CURATE_REWARD"] = BMCHAIN_MIN_CURATE_REWARD;
   result["BMCHAIN_MIN_PERMLINK_LENGTH"] = BMCHAIN_MIN_PERMLINK_LENGTH;
   result["BMCHAIN_MIN_REPLY_INTERVAL"] = BMCHAIN_MIN_REPLY_INTERVAL;
   result["BMCHAIN_MIN_ROOT_COMMENT_INTERVAL"] = BMCHAIN_MIN_ROOT_COMMENT_INTERVAL;
   result["BMCHAIN_MIN_VOTE_INTERVAL_SEC"] = BMCHAIN_MIN_VOTE_INTERVAL_SEC;
   result["BMCHAIN_MINER_ACCOUNT"] = BMCHAIN_MINER_ACCOUNT;
   result["BMCHAIN_MIN_FEEDS"] = BMCHAIN_MIN_FEEDS;
   result["BMCHAIN_MINING_REWARD"] = BMCHAIN_MINING_REWARD;
   result["BMCHAIN_MIN_LIQUIDITY_REWARD"] = BMCHAIN_MIN_LIQUIDITY_REWARD;
   result["BMCHAIN_MIN_PAYOUT"] = BMCHAIN_MIN_PAYOUT;
   result["BMCHAIN_MIN_POW_REWARD"] = BMCHAIN_MIN_POW_REWARD;
   result["BMCHAIN_MIN_PRODUCER_REWARD"] = BMCHAIN_MIN_PRODUCER_REWARD;
   result["BMCHAIN_MIN_TRANSACTION_EXPIRATION_LIMIT"] = BMCHAIN_MIN_TRANSACTION_EXPIRATION_LIMIT;
   result["BMCHAIN_MIN_TRANSACTION_SIZE_LIMIT"] = BMCHAIN_MIN_TRANSACTION_SIZE_LIMIT;
   result["BMCHAIN_MIN_UNDO_HISTORY"] = BMCHAIN_MIN_UNDO_HISTORY;
   result["BMCHAIN_NULL_ACCOUNT"] = BMCHAIN_NULL_ACCOUNT;
   result["BMCHAIN_NUM_INIT_MINERS"] = BMCHAIN_NUM_INIT_MINERS;
   result["BMCHAIN_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM"] = BMCHAIN_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM;
   result["BMCHAIN_OWNER_AUTH_RECOVERY_PERIOD"] = BMCHAIN_OWNER_AUTH_RECOVERY_PERIOD;
   result["BMCHAIN_OWNER_CHALLENGE_COOLDOWN"] = BMCHAIN_OWNER_CHALLENGE_COOLDOWN;
   result["BMCHAIN_OWNER_CHALLENGE_FEE"] = BMCHAIN_OWNER_CHALLENGE_FEE;
   result["BMCHAIN_OWNER_UPDATE_LIMIT"] = BMCHAIN_OWNER_UPDATE_LIMIT;
   result["BMCHAIN_POST_REWARD_FUND_NAME"] = BMCHAIN_POST_REWARD_FUND_NAME;
   result["BMCHAIN_POW_APR_PERCENT"] = BMCHAIN_POW_APR_PERCENT;
   result["BMCHAIN_PRODUCER_APR_PERCENT"] = BMCHAIN_PRODUCER_APR_PERCENT;
   result["BMCHAIN_PROXY_TO_SELF_ACCOUNT"] = BMCHAIN_PROXY_TO_SELF_ACCOUNT;
   result["BMCHAIN_SECONDS_PER_YEAR"] = BMCHAIN_SECONDS_PER_YEAR;
   result["BMCHAIN_RECENT_RSHARES_DECAY_RATE"] = BMCHAIN_RECENT_RSHARES_DECAY_RATE;
   result["BMCHAIN_REVERSE_AUCTION_WINDOW_SECONDS"] = BMCHAIN_REVERSE_AUCTION_WINDOW_SECONDS;
   result["BMCHAIN_ROOT_POST_PARENT"] = BMCHAIN_ROOT_POST_PARENT;
   result["BMCHAIN_SAVINGS_WITHDRAW_REQUEST_LIMIT"] = BMCHAIN_SAVINGS_WITHDRAW_REQUEST_LIMIT;
   result["BMCHAIN_SAVINGS_WITHDRAW_TIME"] = BMCHAIN_SAVINGS_WITHDRAW_TIME;
   result["BMCHAIN_SAVINGS_REWARD_INTERVAL_BLOCKS"] = BMCHAIN_SAVINGS_REWARD_INTERVAL_BLOCKS;
   result["BMCHAIN_SECOND_CASHOUT_WINDOW"] = BMCHAIN_SECOND_CASHOUT_WINDOW;
   result["BMCHAIN_SOFT_MAX_COMMENT_DEPTH"] = BMCHAIN_SOFT_MAX_COMMENT_DEPTH;
   result["BMCHAIN_START_MINER_VOTING_BLOCK"] = BMCHAIN_START_MINER_VOTING_BLOCK;
   result["BMCHAIN_SYMBOL"] = BMCHAIN_SYMBOL;
   result["BMCHAIN_TEMP_ACCOUNT"] = BMCHAIN_TEMP_ACCOUNT;
   result["BMCHAIN_UPVOTE_LOCKOUT"] = BMCHAIN_UPVOTE_LOCKOUT;
   result["BMCHAIN_VOTE_DUST_THRESHOLD"] = BMCHAIN_VOTE_DUST_THRESHOLD;
   result["BMCHAIN_VOTE_REGENERATION_SECONDS"] = BMCHAIN_VOTE_REGENERATION_SECONDS;
   result["BWC_SYMBOL"] = BWC_SYMBOL;
   result["VESTS_SYMBOL"] = VESTS_SYMBOL;
   result["VIRTUAL_SCHEDULE_LAP_LENGTH"] = VIRTUAL_SCHEDULE_LAP_LENGTH;
   result["VIRTUAL_SCHEDULE_LAP_LENGTH2"] = VIRTUAL_SCHEDULE_LAP_LENGTH2;
   result["BMCHAIN_STRESS_TESTING"] = BMCHAIN_STRESS_TESTING;
   result["BMCHAIN_USING_CLOSE_CONTENT"] = BMCHAIN_USING_CLOSE_CONTENT;
   result["BMCHAIN_FIRST_PAYOUT_BLOCK"] = BMCHAIN_FIRST_PAYOUT_BLOCK;
   result["BMCHAIN_VOTE_EMISSION_RATE"] = BMCHAIN_VOTE_EMISSION_RATE;
   result["BMCHAIN_COMMENT_EMISSION_RATE"] = BMCHAIN_COMMENT_EMISSION_RATE;
   result["BMCHAIN_POST_EMISSION_RATE"] = BMCHAIN_POST_EMISSION_RATE;
   result["BMCHAIN_USER_EMISSION_RATE"] = BMCHAIN_USER_EMISSION_RATE;
   result["BMCHAIN_BURN_INIT_REP_BLOCK"] = BMCHAIN_BURN_INIT_REP_BLOCK;
   result["BMCHAIN_DAILY_INFLATION_RATE_RESTRICTION"] = BMCHAIN_DAILY_INFLATION_RATE_RESTRICTION;
   result["CUSTOM_TOKEN_CREATION_FEE"] = CUSTOM_TOKEN_CREATION_FEE;
   result["CUSTOM_TOKEN_UPVOTE_LOCKOUT"] = CUSTOM_TOKEN_UPVOTE_LOCKOUT;
   result["CUSTOM_TOKEN_VESTING_WITHDRAW_INTERVAL_SECONDS"] = CUSTOM_TOKEN_VESTING_WITHDRAW_INTERVAL_SECONDS;

   return result;
}

} } // bmchain::protocol
