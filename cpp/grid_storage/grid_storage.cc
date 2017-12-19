
#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;


template <class T>
void delete_and_null(T* ptr) {
    delete ptr;
    ptr = NULL;
}

class Cell {
public:

    Cell()
        : v_(-1)
    { }

    Cell(int v)
        : v_(v)
    { }

    ~Cell() {
    }

    int value() {
        return v_;
    }

    int set_value(int v) {
        v_ = v;
    }

private:
    int v_;
};


class Row {
    enum { COL_BLOCKSIZE = 1 << 5 };

    class CellBlock {
    public:
        CellBlock(size_t sz) {
            cells_.resize(sz, NULL);
        }

        ~CellBlock() {
            for (size_t i = 0; i < cells_.size(); ++i) {
                delete_and_null(cells_[i]);
            }
        }

        Cell* get_cell(size_t idx) {
            if (idx >= cells_.size()) {
                return NULL;
            }

            return cells_[idx];
        }

        Cell* gain_cell(size_t idx) {
            if (idx >= cells_.size()) {
                assert(false);
                return NULL;
            }

            Cell* c = cells_[idx];
            if (NULL == c) {
                c = new Cell();
                cells_[idx] = c;
            }
            
            return c;
        }

    private:
        vector<Cell*> cells_;
    };

public:
    Row(size_t count)
        : ncols_(count)
        , col_block_size_(COL_BLOCKSIZE)
    {
        size_t block_count = ncols_ / col_block_size_ + (ncols_ % col_block_size_ == 0 ? 0 : 1);
        col_blocks_.resize(block_count, NULL);
    }

    ~Row() {
        for (size_t i = 0; i < col_blocks_.size(); ++i) {
            delete_and_null(col_blocks_[i]);
        }
    }

    int get(size_t col) {
        CellBlock* cb = get_block(col);
        if (NULL == cb) {
            return -1;
        }
        size_t offset = get_block_offset(col);
        return cb->get_cell(offset)->value();
    }

    void set(size_t col, int v) {
        CellBlock* cb = gain_block(col);
        size_t offset = get_block_offset(col);
        Cell* c = cb->gain_cell(offset);
        c->set_value(v);
    }

    size_t get_col_block_size() {
        return col_block_size_;
    }

private:
    CellBlock* get_block(size_t col) {
        if (col >= ncols_) {
            return NULL;
        }
        return col_blocks_[col / col_block_size_];
    }

    CellBlock* gain_block(size_t col) {
        if (col >= ncols_) {
            assert(false);
            return NULL;
        }
        CellBlock* cb = col_blocks_[col / col_block_size_];

        if (NULL == cb) {
            cb = new CellBlock(col_block_size_);
            col_blocks_[col / col_block_size_] = cb;
        }

        return cb;
    }

    int get_block_offset(size_t col) {
        return col % col_block_size_;
    }

private:

    size_t col_block_size_;
    size_t ncols_;
    vector<CellBlock*> col_blocks_;
};


class Grid {
    enum { ROW_BLOCKSIZE = 1 << 4 };

    class RowBlock {
    public:
        RowBlock(size_t block_size, size_t ncol) {
            rows_.resize(block_size, NULL);
            col_size_ = ncol;
        }

        ~RowBlock() {
            for (int i = 0; i < rows_.size(); ++i) {
                delete_and_null(rows_[i]);
            }
        }

        Row* get_row(size_t idx) {
            if (idx >= rows_.size()) {
                return NULL;
            }

            return rows_[idx];
        }

        Row* gain_row(size_t idx) {
            if (idx >= rows_.size()) {
                assert(false);
                return NULL;
            }

            Row* r = rows_[idx];
            if (NULL == r) {
                r = new Row(col_size_);
                rows_[idx] = r;
            }
            return r;
        }


    private:
        vector<Row*> rows_;
        int col_size_;
    };
    
public:
    Grid(int row, int col)
        : nrows_(row)
        , ncols_(col)
        , row_block_size_(ROW_BLOCKSIZE)
    {
        size_t row_block_count = nrows_ / row_block_size_ + (nrows_ % row_block_size_ == 0 ? 0 : 1);
        row_blocks_.resize(row_block_count, NULL);
    }

    ~Grid() {
        for (int i = 0; i < row_blocks_.size(); ++i) {
            delete_and_null(row_blocks_[i]);
        }
    }

    int get(size_t r, size_t c) {
        RowBlock* rb = get_row_block(r);
        if (NULL == rb) {
            return -1;
        }

        size_t offset = get_row_offset(r);
        Row *row = rb->get_row(offset);
        if (NULL == row) {
            return -1;
        }
        
        return row->get(c);
    }

    int set(size_t r, size_t c, int v) {
        RowBlock* rb = gain_row_block(r);
        size_t offset = get_row_offset(r);
        Row *row = rb->gain_row(offset);
        row->set(c, v);
    }


private:
    RowBlock* get_row_block(size_t r) {
        if (r >= nrows_) {
            return NULL;
        }
        return row_blocks_[r / row_block_size_];
    }

    RowBlock* gain_row_block(size_t r) {
        if (r >= nrows_) {
            assert(false);
            return NULL;
        }

        RowBlock* rb = row_blocks_[r / row_block_size_];
        if (NULL == rb) {
            rb = new RowBlock(row_block_size_, ncols_);
            row_blocks_[r / row_block_size_] = rb;
        }
        return rb;
    }

    size_t get_row_offset(size_t r) {
        return r % row_block_size_;
    }

private:
    size_t nrows_;
    size_t ncols_;
    vector<RowBlock*> row_blocks_;
    size_t row_block_size_;
};


int main()
{
    Row r(10000);

    r.set(20, 200);
    r.set(10, 100);
    for (int i = 0; i < 10000; ++i) {
        r.set(i, i);
    }
    for (int i = 0; i < 10000; ++i) {
        assert( r.get(i) == i );
    }

    int count = 0;
    Grid grid(1000, 500);
    grid.set(999, 499, 1);
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 500; ++j) {
            grid.set(i, j, count++);
        }
    }
    count = 0;
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 500; ++j) {
            assert(grid.get(i, j) == count++);
        }
    }

    return 0;
}
