
/* 
    插值查找
    1. 对于数据量较大，关键字分布比较均匀的查找表来说，采用插值查找, 速度较快.
    2. 关键字分布不均匀的情况下，该方法不一定比折半查找要好
*/

template <typename T>
int insertionSearch(std::vector<T>& vec, T key, int low, int high)
{
    if (vec.empty()) return -1;

    while (low <= high) {
        int mid = low + (key - vec[low]) / (vec[high] - vec[low]) * (high - low);
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


