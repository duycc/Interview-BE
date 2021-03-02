
// 希尔排序：每一轮按照事先决定的间隔进行插入排序，间隔会依次缩小，最后一次一定要是1。
template <typename T>
void shellSort(std::vector<T>& vec) 
{
    int size = vec.size();
    int gap = 1;
    while (gap < size / 3) {
        gap = 3 * gap + 1;
    }
    while (gap >= 1) {
        for (int i = gap; i < size; i++) {
            int j = i;
            while (j - gap >= 0) {
                if (vec[j - gap] <= vec[j])  break;

                std::swap(vec[j - gap], vec[j]);
                j -= gap;
            }
        }
        gap /= 3;
    }
    return;
}
