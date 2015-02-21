#ifndef TWOLEVELSIMPLECONFABULATION_H
#define TWOLEVELSIMPLECONFABULATION_H

#include "ForwardConfabulation.h"

class TwoLevelSimpleConfabulation : public ForwardConfabulation
{
public:
    TwoLevelSimpleConfabulation(size_t num_word_modules,
                                const std::string &symbol_file,
                                const std::string &master_file,
                                uint8_t min_single_occurrences,
                                uint8_t min_multi_occurrences);
    TwoLevelSimpleConfabulation(const TwoLevelSimpleConfabulation& rhs) = delete;
    TwoLevelSimpleConfabulation& operator=(const TwoLevelSimpleConfabulation& rhs) = delete;
    TwoLevelSimpleConfabulation(TwoLevelSimpleConfabulation&& rhs) = delete;
    TwoLevelSimpleConfabulation&& operator=(TwoLevelSimpleConfabulation&& rhs) = delete;

    virtual std::vector<std::string> Confabulation(const std::vector<std::string>& symbols, int8_t index_to_complete, bool expectation);

private:
    size_t num_word_modules_;
};

#endif // TWOLEVELSIMPLECONFABULATION_H
