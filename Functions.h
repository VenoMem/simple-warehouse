#ifndef  FUNCTIONS_H
#define FUNCTIONS_H

#include "Storage.h"

void showContents(std::vector<Storage*>& vector_ref);

void addStorage(std::vector<Storage*>& vector_ref);

void addProductToStorage(std::vector<Storage*>& vector_ref);

void addProductToTrolley(std::vector<Storage*>& vector_ref);

void addAmountToStorage(std::vector<Storage*>& vector_ref);

void removeAmountFromStorage(std::vector<Storage*>& vector_ref);

void loadTrolleyFromStorage(std::vector<Storage*>& vector_ref);

void unloadTrolleyToStorage(std::vector<Storage*>& vector_ref);

void unloadTrolley(std::vector<Storage*>& vector_ref);

void removeStorage(std::vector<Storage*>& vector_ref);

void exitProgram(std::vector<Storage*>& vector_ref);

#endif