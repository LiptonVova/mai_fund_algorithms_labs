#ifndef VALIDATE_H
#define VALIDATE_H


#include <stdio.h>

#include "config.h"
#include "utils.h"


error_code_t validate_count_arguments(int argc);
error_code_t validate_link_sender_receiver(unsigned int sender, unsigned int receiver, PostOffice *post_offices, bool* work_post_offices);
error_code_t validate_add_id_postoffice(const bool *work_post_offices, const unsigned int id);
error_code_t validate_number_id_link_postoffice(const bool *work_post_offices, const unsigned int id_link_post_office, const unsigned int id);
error_code_t validate_delete_id_postoffice(const bool *work_post_offices, const unsigned int id);
error_code_t validate_type_letter(TypeLetter type_letter);
bool validate_work_post_office(PostOffice *post_offices, bool *work_post_offices, bool *links, int *distance, unsigned int next_id_post_office);

#endif