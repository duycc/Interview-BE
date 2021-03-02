
// 堆排序：（最大堆，有序区）。从堆顶把根卸出来放在有序区之前，再恢复堆。
template <typename T>
void adjustHeap(std::vector<T>& vec, int start, int len)
{
	int dad = start;
	int son = 2 * start + 1;

	while (son < len) {
		if (son + 1 < len && vec[son + 1] > vec[son])
			son++;
		if (vec[dad] >= vec[son]) // =?
			return;
		else {
			std::swap(vec[dad], vec[son]);
			dad = son;
			son = 2 * son + 1;
		}
	}
}

template <typename T>
void heapSort(std::vector<T>& vec)
{
	// 初始化
	for (int i = vec.size() / 2 - 1; i >= 0; --i) {
		adjustHeap(vec, i, vec.size());
	}

	// 交换元素，调整堆
	for (int i = vec.size() - 1; i > 0; --i) {
		std::swap(vec[0], vec[i]);
		adjustHeap(vec, 0, i);
	}

	return;
}
