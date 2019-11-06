#include "statisticians.hpp"

#include <vector>
#include <iterator>
#include <algorithm>

namespace statisticians {

    class SubGrid;

    class Grid {
    public:
        Grid() = default;

        static Grid parse(std::istream& in, int h, int w) {
            std::vector<int> values(h * w);
            std::copy_n(std::istream_iterator<int>(in), h * w, values.begin());
            return Grid(h, w, std::move(values));
        }

        std::pair<int, int> size() const {
            return {height_, width_};
        }

        int height() const {
            return height_;
        }

        int width() const {
            return width_;
        }

        int area() const {
            return height_ * width_;
        }

        int at(int i, int j) const {
            return values_[i * width_ + j];
        }

        SubGrid subgrid(int i, int j, int h, int w) const;

    protected:
        explicit Grid(int h, int w, std::vector<int> values)
                : values_(std::move(values)),
                  height_(h),
                  width_(w) {}

    private:
        std::vector<int> values_;
        int height_ = 0, width_ = 0;
    };

    class SubGrid {

        std::pair<int, int> size() const {
            return {height_, width_};
        }

        int height() const {
            return height_;
        }

        int width() const {
            return width_;
        }

        int area() const {
            return height_ * width_;
        }

        int at(int i, int j) const {
            return grid_.at(i + i_offset_, j + j_offset_);
        }

        SubGrid subgrid(int i, int j, int h, int w) const;

    protected:
        SubGrid(const Grid& grid, int i, int j, int h, int w) :
            grid_(grid),
            i_offset_(i),
            j_offset_(j),
            height_(h),
            width_(w) {}


    private:
        const Grid& grid_;
        int i_offset_ = 0, j_offset_ = 0;
        int height_ = 0, width_ = 0;

        friend class Grid;
    };

    SubGrid Grid::subgrid(int i, int j, int h, int w) const {
        return {*this, i, j, h, w};
    }

    SubGrid SubGrid::subgrid(int i, int j, int h, int w) const {
        return grid_.subgrid(i + i_offset_, j + j_offset_, h, w);
    }

    void solution(std::istream& in, std::ostream& out) {
        int h, w;
        in >> h >> w;

        int a, b;
        std::cin >> a >> b;

        Grid grid = Grid::parse(in, h, w);

        out << grid.area() << std::endl;
    }

} // namespace statisticians
