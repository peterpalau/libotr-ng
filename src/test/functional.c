/*
 *  This file is part of the Off-the-Record Next Generation Messaging
 *  library (libotr-ng).
 *
 *  Copyright (C) 2016-2018, the libotr-ng contributors.
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib.h>
#include <gcrypt.h>
#include "otrng.h"

#include "functionals/all.h"

int main(int argc, char **argv) {
  if (!gcry_check_version(GCRYPT_VERSION))
    return 2;

  gcry_control(GCRYCTL_INIT_SECMEM, 0); // disable secure memory for tests
  gcry_control(GCRYCTL_RESUME_SECMEM_WARN);
  gcry_control(GCRYCTL_ENABLE_QUICK_RANDOM, 0);
  gcry_control(GCRYCTL_INITIALIZATION_FINISHED);

  OTRNG_INIT;

  g_test_init(&argc, &argv, NULL);

  REGISTER_FUNCTIONALS;

  /* g_test_add_func("/list/add", test_otrng_list_add); */
  /* g_test_add_func("/list/copy", test_otrng_list_copy); */
  /* g_test_add_func("/list/insert_at_n", test_otrng_list_insert_at_n); */
  /* g_test_add_func("/list/get", test_otrng_list_get_last); */
  /* g_test_add_func("/list/get_by_value", test_otrng_list_get_by_value); */
  /* g_test_add_func("/list/length", test_otrng_list_len); */
  /* g_test_add_func("/list/empty_size", test_list_empty_size); */

  /* g_test_add_func("/dh/api", dh_test_api); */
  /* g_test_add_func("/dh/serialize", dh_test_serialize); */
  /* g_test_add_func("/dh/shared-secret", dh_test_shared_secret); */
  /* g_test_add_func("/dh/destroy", dh_test_keypair_destroy); */

  /* g_test_add_func("/ring-signature/rsig_auth", test_rsig_auth); */
  /* g_test_add_func("/ring-signature/calculate_c", test_rsig_calculate_c); */
  /* g_test_add_func("/ring-signature/compatible_with_prekey_server", */
  /*                 test_rsig_compatible_with_prekey_server); */

  /* g_test_add_func("/serialize_and_deserialize/uint", test_ser_deser_uint); */
  /* g_test_add_func("/serialize_and_deserialize/data", */
  /*                 test_serialize_otrng_deserialize_data); */

  /* g_test_add_func("/serialize/dh-public-key", */
  /*                 test_otrng_serialize_dh_public_key); */
  /* g_test_add_func("/serialize_and_deserialize/ed448-public-key", */
  /*                 test_ser_des_otrng_public_key); */
  /* g_test_add_func("/serialize_and_deserialize/ed448-shared-prekey", */
  /*                 test_ser_des_otrng_shared_prekey); */
  /* g_test_add_func("/serialize/otrng-symmetric-key", */
  /*                 test_serialize_otrng_symmetric_key); */
  /* g_test_add_func("/serialize/fingerprint", test_serializes_fingerprint); */

  /* g_test_add_func("/client_profile/build_client_profile", */
  /*                 test_otrng_client_profile_build); */
  /* g_test_add_func("/client_profile/create", test_client_profile_create); */
  /* g_test_add_func("/client_profile/serialize_body", */
  /*                 test_client_profile_serializes_body); */
  /* g_test_add_func("/client_profile/serialize", test_client_profile_serializes); */
  /* g_test_add_func("/client_profile/deserializes", */
  /*                 test_otrng_client_profile_deserializes); */
  /* g_test_add_func("/client_profile/sign_and_verifies", */
  /*                 test_client_profile_signs_and_verify); */
  /* g_test_add_func("/client_profile/transitional_signature", */
  /*                 test_otrng_client_profile_transitional_signature); */

  /* g_test_add_func("/dake/build_interactive_rsign_tag", */
  /*                 test_build_interactive_rsign_tag); */

  /* WITH_DAKE_FIXTURE("/dake/non_interactive_auth_message/serialize", */
  /*                   test_dake_non_interactive_auth_message_serializes); */
  /* WITH_DAKE_FIXTURE("/dake/non_interactive_auth_message/deserialize", */
  /*                   test_otrng_dake_non_interactive_auth_message_deserializes); */

  /* WITH_DAKE_FIXTURE("/dake/identity_message/serializes", */
  /*                   test_dake_identity_message_serializes); */
  /* WITH_DAKE_FIXTURE("/dake/identity_message/deserializes", */
  /*                   test_otrng_dake_identity_message_deserializes); */
  /* WITH_DAKE_FIXTURE("/dake/identity_message/valid", */
  /*                   test_dake_identity_message_valid); */

  /* g_test_add_func("/dake/prekey_message/serializes", */
  /*                 test_dake_prekey_message_serializes); */
  /* g_test_add_func("/dake/prekey_message/deserializes", */
  /*                 test_otrng_dake_prekey_message_deserializes); */
  /* WITH_DAKE_FIXTURE("/dake/prekey_message/valid", */
  /*                   test_dake_prekey_message_valid); */

  /* g_test_add_func("/data_message/valid", test_data_message_valid); */
  /* g_test_add_func("/data_message/serialize", test_data_message_serializes); */
  /* g_test_add_func("/data_message/serialize_absent_dh", */
  /*                 test_data_message_serializes_absent_dh); */
  /* g_test_add_func("/data_message/deserialize", */
  /*                 test_otrng_data_message_deserializes); */

  /* g_test_add_func("/fragment/create_fragments_smaller_than_max_size", */
  /*                 test_create_fragments_smaller_than_max_size); */
  /* g_test_add_func("/fragment/create_fragments", test_create_fragments); */
  /* g_test_add_func("/fragment/defragment_message", */
  /*                 test_defragment_valid_message); */
  /* g_test_add_func("/fragment/defragment_single_fragment", */
  /*                 test_defragment_single_fragment); */
  /* g_test_add_func("/fragment/defragment_out_of_order_message", */
  /*                 test_defragment_out_of_order_message); */
  /* g_test_add_func("/fragment/defragment_fails_without_comma", */
  /*                 test_defragment_without_comma_fails); */
  /* g_test_add_func("/fragment/defragment_with_different_total_fails", */
  /*                 test_defragment_with_different_total_fails); */
  /* g_test_add_func("/fragment/defragment_fragment_twice_fails", */
  /*                 test_defragment_fragment_twice_fails); */
  /* g_test_add_func("/fragment/fails_for_another_instance", */
  /*                 test_defragment_fails_for_another_instance); */
  /* g_test_add_func("/fragment/defragment_regular_otr_message", */
  /*                 test_defragment_regular_otr_message); */
  /* g_test_add_func("/fragment/defragment_two_messages", */
  /*                 test_defragment_two_messages); */
  /* g_test_add_func("/fragment/expiration_of_fragments", */
  /*                 test_expiration_of_fragments); */

  /* g_test_add_func("/key_management/derive_ratchet_keys", */
  /*                 test_derive_ratchet_keys); */
  /* g_test_add_func("/key_management/ssid", test_calculate_ssid); */
  /* g_test_add_func("/key_management/extra_symm_key", */
  /*                 test_calculate_extra_symm_key); */
  /* g_test_add_func("/key_management/brace_key", test_calculate_brace_key); */

  /* g_test_add_func("/smp/state_machine", test_smp_state_machine); */
  /* g_test_add_func("/smp/state_machine_abort", test_smp_state_machine_abort); */
  /* g_test_add_func("/smp/generate_secret", test_otrng_generate_smp_secret); */
  /* g_test_add_func("/smp/msg_1_asprintf_null_question", */
  /*                 test_otrng_smp_msg_1_asprintf_null_question); */
  /* g_test_add_func("/tlv/parse", test_tlv_parse); */
  /* g_test_add_func("/tlv/append", test_otrng_append_tlv); */
  /* g_test_add_func("/tlv/append_padding", test_otrng_append_padding_tlv); */

  /* g_test_add("/otrng/builds_query_message", otrng_fixture_s, NULL, */
  /*            otrng_fixture_set_up, test_otrng_builds_query_message, */
  /*            otrng_fixture_teardown); */
  /* g_test_add("/otrng/builds_query_message_v34", otrng_fixture_s, NULL, */
  /*            otrng_fixture_set_up, test_otrng_builds_query_message_v34, */
  /*            otrng_fixture_teardown); */
  /* g_test_add("/otrng/builds_whitespace_tag", otrng_fixture_s, NULL, */
  /*            otrng_fixture_set_up, test_otrng_builds_whitespace_tag, */
  /*            otrng_fixture_teardown); */
  /* g_test_add("/otrng/builds_whitespace_tag_v34", otrng_fixture_s, NULL, */
  /*            otrng_fixture_set_up, test_otrng_builds_whitespace_tag_v34, */
  /*            otrng_fixture_teardown); */
  /* g_test_add("/otrng/receives_plaintext_without_ws_tag_on_start", */
  /*            otrng_fixture_s, NULL, otrng_fixture_set_up, */
  /*            test_otrng_receives_plaintext_without_ws_tag_on_start, */
  /*            otrng_fixture_teardown); */
  /* g_test_add("/otrng/receives_plaintext_without_ws_tag_not_on_start", */
  /*            otrng_fixture_s, NULL, otrng_fixture_set_up, */
  /*            test_otrng_receives_plaintext_without_ws_tag_not_on_start, */
  /*            otrng_fixture_teardown); */
  /* g_test_add("/otrng/receives_plaintext_with_ws_tag", otrng_fixture_s, NULL, */
  /*            otrng_fixture_set_up, test_otrng_receives_plaintext_with_ws_tag, */
  /*            otrng_fixture_teardown); */
  /* g_test_add("/otrng/receives_plaintext_with_ws_tag_after_text", */
  /*            otrng_fixture_s, NULL, otrng_fixture_set_up, */
  /*            test_otrng_receives_plaintext_with_ws_tag_after_text, */
  /*            otrng_fixture_teardown); */
  /* g_test_add("/otrng/receives_plaintext_with_ws_tag_v3", otrng_fixture_s, NULL, */
  /*            otrng_fixture_set_up, test_otrng_receives_plaintext_with_ws_tag_v3, */
  /*            otrng_fixture_teardown); */
  /* g_test_add("/otrng/receives_query_message", otrng_fixture_s, NULL, */
  /*            otrng_fixture_set_up, test_otrng_receives_query_message, */
  /*            otrng_fixture_teardown); */
  /* g_test_add("/otrng/receives_query_message_v3", otrng_fixture_s, NULL, */
  /*            otrng_fixture_set_up, test_otrng_receives_query_message_v3, */
  /*            otrng_fixture_teardown); */
  /* g_test_add_func("/otrng/destroy", test_otrng_destroy); */

  /* g_test_add_func("/otrng/callbacks/shared_session_state", */
  /*                 test_otrng_invokes_shared_session_state_callbacks); */
  /* g_test_add_func("/otrng/shared_session_state/serializes", */
  /*                 test_otrng_generates_shared_session_state_string); */
  /* g_test_add_func("/otrng/build_prekey_ensemble", */
  /*                 test_otrng_build_prekey_ensemble); */

  /* g_test_add_func("/prekey_profile/validates", test_prekey_profile_validates); */
  /* g_test_add_func("/prekey_profile/serialize", test_prekey_profile_serialize); */
  /* g_test_add_func("/prekey_profile/deserialize", */
  /*                 test_prekey_profile_deserialize); */
  /* g_test_add_func("/prekey_ensemble/validate", test_prekey_ensemble_validate); */

  /* g_test_add_func("/prekey_server/dake/dake-1/serialize", */
  /*                 test_prekey_dake1_message_serialize); */
  /* g_test_add_func("/prekey_server/dake/dake-2/deserialize", */
  /*                 test_prekey_dake2_message_deserialize); */
  /* g_test_add_func("/prekey_server/dake/dake-3/storage_info_request", */
  /*                 test_prekey_dake3_message_append_storage_info_req); */
  /* g_test_add_func("/prekey_server/dake/dake-3/serialize", */
  /*                 test_prekey_dake3_message_serialize); */
  /* g_test_add_func("/prekey_server/dake/storage-status/deserialize", */
  /*                 test_prekey_storage_status_message_deserialize); */
  /* g_test_add_func("/prekey_server/dake/ensemble-retrieval/deserialize", */
  /*                 test_prekey_ensemble_retrieval_message_deserialize); */
  /* g_test_add_func("/prekey_server/proofs/dh_gen_validation", */
  /*                 test_dh_proof_generation_and_validation); */
  /* g_test_add_func("/prekey_server/proofs/ecdh_gen_validation", */
  /*                 test_ecdh_proof_generation_and_validation); */
  /* /\* g_test_add_func("/prekey_server/proofs/dh/verify/fixed", *\/ */
  /* /\*                 test_dh_proof_validates_specific_values); *\/ */
  /* g_test_add_func("/prekey_server/proofs/dh/gen_and_verify/fixed", */
  /*                 test_dh_proof_generation_and_validation_specific_values); */
  /* g_test_add_func("/prekey_server/proofs/ecdh/serialization", */
  /*                 test_ecdh_proof_serialization); */
  /* g_test_add_func("/prekey_server/proofs/dh/serialization", */
  /*                 test_dh_proof_serialization); */
  /* g_test_add_func("/prekey_server/proofs/ecdh/deserialization", */
  /*                 test_ecdh_proof_deserialization); */
  /* g_test_add_func("/prekey_server/proofs/dh/deserialization", */
  /*                 test_dh_proof_deserialization); */

  /* g_test_add_func("/prekey_server_client/send_dake_1_message", */
  /*                 test_send_dake_1_message); */
  /* g_test_add_func( */
  /*     "/prekey_server_client/send_dake_3_message_with_storage_info_request", */
  /*     test_send_dake_3_message_with_storage_info_request); */
  /* g_test_add_func("/prekey_server_client/receive_prekey_server_messages", */
  /*                 test_receive_prekey_server_messages); */

  /* g_test_add_func("/prekey_messages/deserialize_prekey_success_message", */
  /*                 test_deserialize_prekey_success_message); */

  /* g_test_add_func("/client/conversation_api", test_client_conversation_api); */
  /* g_test_add_func("/client/api", test_client_api); */
  /* g_test_add_func("/client/get_our_fingerprint", */
  /*                 test_client_get_our_fingerprint); */
  /* g_test_add_func("/client/fingerprint_to_human", */
  /*                 test_fingerprint_hash_to_human); */
  /* g_test_add_func("/client/sends_fragments", */
  /*                 test_client_sends_fragmented_message); */
  /* g_test_add_func("/client/receives_fragments", */
  /*                 test_client_receives_fragmented_message); */
  /* g_test_add_func("/client/expires_old_fragments", */
  /*                 test_client_expires_old_fragments); */

  /* g_test_add_func("/client/conversation_data_message_multiple_locations", */
  /*                 test_conversation_with_multiple_locations); */
  /* g_test_add_func("/client/identity_message_in_waiting_auth_i", */
  /*                 test_valid_identity_msg_in_waiting_auth_i); */
  /* g_test_add_func("/client/identity_message_in_waiting_auth_r", */
  /*                 test_valid_identity_msg_in_waiting_auth_r); */
  /* g_test_add_func("/client/invalid_auth_r_msg_in_not_waiting_auth_r", */
  /*                 test_invalid_auth_r_msg_in_not_waiting_auth_r); */
  /* g_test_add_func("/client/invalid_auth_i_msg_in_not_waiting_auth_i", */
  /*                 test_invalid_auth_i_msg_in_not_waiting_auth_i); */

  /* // API are supposed to test the public API. */
  /* // They go to the end because they are integration tests, and we only should */
  /* // care about them after all the unit tests are working. */
  /* // TODO: @refactoring There is TOO MUCH /api tests. They are TOO BIG and hard */
  /* // to understand (by nature, I think). Let's reconsider what should be here. */

  /* g_test_add_func("/double_ratchet/in_order/new_sending_ratchet/v4", */
  /*                 test_double_ratchet_new_sending_ratchet_in_order); */
  /* g_test_add_func("/double_ratchet/out_of_order/same_ratchet/v4", */
  /*                 test_double_ratchet_same_ratchet_out_of_order); */
  /* g_test_add_func("/double_ratchet/out_of_order/new_ratchet/v4", */
  /*                 test_double_ratchet_new_ratchet_out_of_order); */
  /* g_test_add_func("/double_ratchet/corrupted_ratchet/v4", */
  /*                 test_double_ratchet_corrupted_ratchet); */

  /* g_test_add_func("/api/interactive_conversation/v4", */
  /*                 test_api_interactive_conversation); */
  /* g_test_add_func("/api/send_offline_message", test_otrng_send_offline_message); */
  /* g_test_add_func("/api/incorrect_offline_dake", */
  /*                 test_otrng_incorrect_offline_dake); */

  /* g_test_add_func("/api/multiple_clients", test_api_multiple_clients); */
  /* g_test_add_func("/api/conversation_errors_1", test_api_conversation_errors_1); */
  /* g_test_add_func("/api/conversation_errors_2", test_api_conversation_errors_2); */
  /* g_test_add_func("/api/conversation/v3", test_api_conversation_v3); */
  /* g_test_add_func("/api/smp", test_api_smp); */
  /* g_test_add_func("/api/smp_abort", test_api_smp_abort); */
  /* /\* g_test_add_func("/api/messaging", test_api_messaging); *\/ */
  /* g_test_add_func("/api/extra_symm_key", test_api_extra_sym_key); */
  /* g_test_add_func("/api/heartbeat_messages", test_heartbeat_messages); */

  int ret = g_test_run();
  OTRNG_FREE;
  return ret;
}