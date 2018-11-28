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

#pragma once

#include <string>
#include <memory>

#include "sparse_structures/DOKLinksMatrix.hpp"
#include "sparse_structures/SparseHashLinksMatrix.hpp"
#include "sparse_structures/CSRLinksMatrix.hpp"
#include "SymbolMapping.h"

class KnowledgeBase
{
public:
	KnowledgeBase(const std::string& id, const SymbolMapping& src_map, const SymbolMapping& targ_map);
	KnowledgeBase(const KnowledgeBase& rhs) = delete;
	KnowledgeBase& operator=(const KnowledgeBase& rhs) = delete;
	KnowledgeBase(KnowledgeBase&& rhs) = delete;
	KnowledgeBase&& operator=(KnowledgeBase&& rhs) = delete;

	void Add(const std::string& src_symbol, const std::string& targ_symbol);
	void Add(uint16_t targ_index, uint16_t src_index);
	void ComputeLinkStrengths();

	std::unique_ptr<IExcitationVector<uint16_t, float>> Transmit(const IExcitationVector<uint16_t, float>& normalized_excitations) const;

	void ResetCooccurrenceCounts() { cooccurrence_counts_.reset(); }
	void ResetTargetSymbolSums() { target_symbol_sums_.clear(); }
	std::string GetId() const { return id_; }
	std::string GetStats() const { return std::string("number of knowledge links: ") + std::to_string(GetNumKnowledgeLinks()); }
	uint16_t GetSizeSrc() const { return cooccurrence_counts_->GetNumRows(); }
	uint16_t GetSizeTarg() const { return cooccurrence_counts_->GetNumCols(); }
	uint32_t GetNumKnowledgeLinks() const { return kbase_->GetNnz(); }

private:
	// The knowledge base is essentially a matrix of conditional probabilities P(s | t)
	// Symbols s are providing the input excitations that pass through the knowledge base
	// In order to be able to transmit excitations with regular matrix multiplication
	// the source symbols must correspond to the COLUMNS of the matrix
	// and the target symbols to the ROWS of the matrix
	// (hence target_symbol_sums_ are essentially the row sums)

	const std::string id_;
	const SymbolMapping& src_map_;
	const SymbolMapping& targ_map_;
	std::unique_ptr<IKnowledgeLinks<uint16_t, uint16_t, uint32_t>> cooccurrence_counts_;
	std::unique_ptr<IKnowledgeLinks<uint16_t, uint16_t, float>> kbase_;
	std::vector<uint32_t> target_symbol_sums_;

	static float ComputeLinkStrength(double antecedent_support_probability);
};
