
// 顺序查找，注意设置哨兵
template <typename T>
int sequentialSearch(std::vector<T>& vec, T key)
{
    T tmp = vec[vec.size() - 1];
    vec[vec.size() - 1] = key;
    int i = 0;
    while (vec[i] != key) {
        i++;
    }
    vec[vec.size() - 1] = tmp;
    if (i < vec.size() - 1 || tmp == key) {
        return i;
    }

    return -1;
}
