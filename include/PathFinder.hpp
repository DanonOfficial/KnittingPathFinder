//
// Created by roundedglint585 on 6/11/19.
//

#ifndef KNITTINGPATHFINDER_PATHFINDER_HPP
#define KNITTINGPATHFINDER_PATHFINDER_HPP


#include <vector>
#include <optional>
#include <cstdint>
#include <queue>
#include <stack>

class PathFinder {

public:

    std::optional<std::vector<std::pair<std::size_t, std::size_t>>>
    operator()(const std::vector<std::vector<uint8_t >> &bitmap);

private:

    bool checkCloseLeftUp(const std::pair<std::size_t, std::size_t> &position,
                          const std::vector<std::vector<uint8_t >> &bitmap, uint8_t visitationStatus);

    bool checkCloseRightUp(const std::pair<std::size_t, std::size_t> &position,
                           const std::vector<std::vector<uint8_t >> &bitmap, uint8_t visitationStatus);

    bool checkCloseLeftDown(const std::pair<std::size_t, std::size_t> &position,
                            const std::vector<std::vector<uint8_t >> &bitmap, uint8_t visitationStatus);

    bool checkCloseRightDown(const std::pair<std::size_t, std::size_t> &position,
                             const std::vector<std::vector<uint8_t >> &bitmap, uint8_t visitationStatus);

    bool checkFarLeftUp(const std::pair<std::size_t, std::size_t> &position,
                        const std::vector<std::vector<uint8_t >> &bitmap, uint8_t visitationStatus);

    bool checkFarRightUp(const std::pair<std::size_t, std::size_t> &position,
                         const std::vector<std::vector<uint8_t >> &bitmap, uint8_t visitationStatus);

    bool checkFarLeftDown(const std::pair<std::size_t, std::size_t> &position,
                          const std::vector<std::vector<uint8_t >> &bitmap, uint8_t visitationStatus);

    bool checkFarRightDown(const std::pair<std::size_t, std::size_t> &position,
                           const std::vector<std::vector<uint8_t >> &bitmap, uint8_t visitationStatus);

    bool isFullyCovered(const std::vector<std::vector<uint8_t>> &bitmap) const;

    //Visited mostly used to check how we crossed cell: if 0 then not crossed, if 1 then /, else if 2 then \, otherwise 3
    //Its actually binary codes systme for every situation: 00, 01, 10, 11
    std::vector<std::vector<uint8_t >> visited_;
    std::size_t width_, height_;
    std::vector<std::pair<std::size_t, std::size_t>> path_;
};


#endif //KNITTINGPATHFINDER_PATHFINDER_HPP
