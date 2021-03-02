
// 基数排序：一种多关键字的排序算法，可用桶排序实现。

template <typename T>
void radixSort(std::vector<T>& vec)
{
    T max = *std::max_element(vec.begin(), vec.end());
    int maxLen = std::to_string(max).size();

    vector<vector<T>> bucketArr(10);

    for (int i{}; i < maxLen; ++i) {
        for (T& elem : vec) {
            int num = static_cast<int>(elem / pow(10, i)) % 10;
            bucketArr[num].push_back(elem);
        }

        // 收集数据并存入vec
        auto iter = vec.begin();
        for (auto it = bucketArr.begin(); it != bucketArr.end(); ++it) {
            std::copy((*it).begin(), (*it).end(), iter);
            std::advance(iter, (*it).size());
            (*it).clear();	// 每次需要清空桶内元素
        }
    }

    return;
}