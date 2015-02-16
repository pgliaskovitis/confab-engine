/*
 * Copyright 2014 Periklis G. Liaskovitis
 *
 * This file is part of confab-engine.
 *
 * confab-engine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * confab-engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with confab-engine.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <vector>
#include <set>
#include <sparse_structures/IExcitationVector.hpp>
#include <SymbolMapping.h>

class Module
{
public:
    Module(const SymbolMapping& symbol_mapping);
    Module(const Module& rhs) = delete;
    Module& operator=(const Module& rhs) = delete;
    Module(Module&& rhs) = delete;
    Module&& operator=(Module&& rhs) = delete;

    void Reset();
    void ExcitationsToZero();

    void ActivateSymbol(const std::string& word, int K);

    void AddExcitationToIndex(unsigned long index, float value);
    void AddExcitationToAllSymbols(int K);

    void AddExcitationVector(const IExcitationVector<float>& input);

    void Freeze();
    void Unfreeze();
    bool IsFrozen() const { return frozen_indexes_ != nullptr; }

    const std::unique_ptr<IExcitationVector<float>>& GetNormalizedExcitations();
    std::vector<std::string> GetExpectation();

    std::string ElementaryConfabulation();
    std::string ElementaryConfabulation(int K);

    std::vector<std::string> PartialConfabulation(int K, bool multiconf);

    const SymbolMapping& get_symbol_mapping() { return symbol_mapping_; }

private:
    const SymbolMapping& symbol_mapping_;

    std::unique_ptr<IExcitationVector<float>> excitations_;
    std::unique_ptr<IExcitationVector<float>> normalized_excitations_;
    std::unique_ptr<IExcitationVector<int>> kb_inputs_;
    std::unique_ptr<std::set<unsigned long>> frozen_indexes_;

    std::unique_ptr<std::pair<unsigned long, float>> MaxExcitation(const std::set<std::pair<unsigned long, float>>& nz_excitations);
    std::set<std::pair<unsigned long, float>> ExcitationsAbove(int K, const std::set<std::pair<unsigned long, float>>& nz_excitations);
    int ActualK(int K);
    int MaxK();
};

#endif // MODULE_H
