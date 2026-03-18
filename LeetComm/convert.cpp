class Solution {
    public:
        string convert(string s, int numRows) {
            if (numRows == 1) return s; // 特殊情况：无变化
            
            vector<string> rows(numRows); // 每一行的字符串
            int curRow = 0;               // 当前所在行
            int step = -1;                // 移动方向：-1 向上，1 向下
            
            for (char c : s) {
                rows[curRow] += c;        // 将字符放入当前行
                // 到达边界时反转方向
                if (curRow == 0 || curRow == numRows - 1) {
                    step = -step;
                }
                curRow += step;           // 移动到下一行
            }
            
            // 拼接所有行得到结果
            string res;
            for (string& row : rows) {
                res += row;
            }
            return res;
        }
    };