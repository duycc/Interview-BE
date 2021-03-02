
// 二分查找（折半查找）：对于已排序，若无序，需要先排序

/**************
    递归版
**************/
template <typename T>
int binary_search_recursive(std::vector<T>& vec, T& key, int low, int high)
{
    if (low > high) return -1;

    int mid = (high - low) / 2 + low;

    if (vec[mid] == key) return mid;
    else if (vec[mid] > key) {
        return binary_search_recursive(vec, key, low, mid - 1);
    }
    else {
        return binary_search_recursive(vec, key, mid + 1, high);
    }

    return -1;
}


/**************
    迭代版
**************/
template <typename T>
int binary_search_iter(std::vector<T>& vec, T key, int low, int high)
{
    if (vec.empty()) return -1;

    while (low <= high) {
        int mid = (high - low) / 2 + low;
        if (vec[mid] == key) {
            return mid;
        }
        else if (vec[mid] > key) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    return -1;
}