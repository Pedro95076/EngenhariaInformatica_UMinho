#ifndef HANDLER_H
#define HANDLER_H

#include "message.h"
#include "hashtable.h"

void handle_message(HashTable h, Message message, char* pids_file);

#endif // HANDLER_H