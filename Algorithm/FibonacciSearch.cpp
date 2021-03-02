
const int FIBO_MAX_SIZE = 20;

template <typename T>
int fibonacciSearch(std::vector<T>& vec, T key, int low, int high)
{
    int len = vec.size();
    // 1. 构建fibonacci数列
    std::vector<int> fiboArr(FIBO_MAX_SIZE, 0);
    fiboArr[1] = 1;
    for (int i = 2; i < FIBO_MAX_SIZE; ++i) {
        fiboArr[i] = fiboArr[i - 2] + fiboArr[i - 1];
    }

    // 2. 计算数据长度对应fibonacci数列元素
    int index = 0;
    while (fiboArr[index] <= len) { 
        index++;
    }
    
    // 3. 最大值填充元素
    for (int i = len; i < fiboArr[index] - 1; ++i) {
        vec.push_back(vec.back());
    }

    // 4. 开始查找
    while (low <= high) {
        int mid = low + fiboArr[--index] - 1;
        if (vec[mid] == key) {
            if (mid < len) {
                return mid;		// 查找成功
            }
            else {
                return len - 1;	// 补充元素
            }
        }
        else if (vec[mid] > key) {
            high = mid - 1;
            index = index - 1;
        }
        else {
            low = mid + 1;
            index = index - 2;
        }
    }
    return -1;
}
