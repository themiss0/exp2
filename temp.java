class Solution {
    public String getSmallestString(String s) {
        int[] arr = new int[2];
        int p = 0;
        arr[0] = s.charAt(0) - '0';

        StringBuilder sb = new StringBuilder(s);

        for (int i = 1; i < s.length(); i++) {
            arr[(++p) % 2] = s.charAt(i) - '0';

            if (arr[(p - 1) % 2] % 2 == arr[p % 2] % 2) {
                if (arr[(p - 1) % 2] > arr[p % 2]) {
                    sb.setCharAt(i, (char) (arr[(p - 1) % 2] + '0'));
                    sb.setCharAt(i - 1, (char) (arr[p % 2] + '0'));
                    break;
                }
            }
        }

        return sb.toString();
    }

    public static void main(String[] args) {
        new Solution().getSmallestString("45320");
    }
}