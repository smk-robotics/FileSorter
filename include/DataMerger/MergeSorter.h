/**
 * @file MergeSorter.h
 * @author Smirnov Kirill <smk.robotics@gmail.com>
 * @brief MergeSorter class.
 * @details Class for merge sorting data from chunks.
 */

#pragma once

#include "Chunk.h"

namespace file_sorter {

class MergeSorter {
public:
    MergeSorter()  = default;
    ~MergeSorter() = default;
    template<template<class ...> class TContainer, class TChunk>
    void merge(const TContainer<TChunk>& chunks) const;
// private:
//     MergeStrategy merger;
};

} // file_sorter namespace.