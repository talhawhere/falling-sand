
            else if (isEmpty(x + 1, y + 1)) { //checks if there is space below + right
                swap(grid[idx(x, y)], grid[idx(x + 1, y + 1)]);