// class Solution {
// public:
//     void merge(int A[], int m, int B[], int n) {
//         if(n == 0){
//             return;
//         }
//         if(m == 0){
//             for(int i = 0; i < n; ++i){
//                 A[i] = B[i];
//             }
//             return;
//         }

//         for(int i = m - 1; i >= 0; --i){
//             A[i + n] = A[i];
//         }

//         int i = n, j = 0;
//         int start = 0;

//         while(i < m+n && j < n){
//             if(A[i] <= B[j]){
//                 A[start++] = A[i++];
//             }else{
//                 A[start++] = B[j++];
//             }
//         }

//         while(i < m+n){
//             A[start++] = A[i++];
//         }

//         while(j < n){
//             A[start++] = B[j++];
//         }
//     }
// };

// 倒序的归并更好

class Solution {
public:
  void merge(int A[], int m, int B[], int n) {
    int i = m - 1;     // A数组的有效元素末尾
    int j = n - 1;     // B数组的末尾
    int k = m + n - 1; // 合并后的数组末尾

    // 从后往前合并
    while (i >= 0 && j >= 0) {
      if (A[i] > B[j]) {
        A[k--] = A[i--];
      } else {
        A[k--] = B[j--];
      }
    }

    // 如果B数组还有剩余元素
    while (j >= 0) {
      A[k--] = B[j--];
    }
    // 如果A数组还有剩余元素，它们已经在正确位置，不需要处理
  }
};