echo 正确 >> test.out
作业相似度匹配参数解析.exe 1234567 1234567 test.cpp 80 screen >> test .out
echo 正确 >> test.out
作业相似度匹配参数解析.exe 1234567 all test.cpp 80 screen >> test .out
echo 正确 >> test.out
作业相似度匹配参数解析.exe all all test.cpp 80 screen >> test .out
echo 前一个为all，后一个不是all但正确 >> test.out
作业相似度匹配参数解析.exe all 1234567 test.cpp 80 screen >> test .out
echo 前一个为all，后一个不是all学号错误 >> test.out
作业相似度匹配参数解析.exe all 123457 test.cpp 80 screen >> test .out
echo 前一个为all，后一个不是all学号错误 >> test.out
作业相似度匹配参数解析.exe all 123457A test.cpp 80 screen >> test .out
echo 第一个学号正确，第二个错误 >> test.out
作业相似度匹配参数解析.exe 1234567 123457A test.cpp 80 screen >> test .out
echo 第一个学号正确，第二个错误 >> test.out
作业相似度匹配参数解析.exe 1234567 12357A test.cpp 80 screen >> test .out
echo 第一个学号正确，第二个错误 >> test.out
作业相似度匹配参数解析.exe 1234567 1234578 test.cpp 80 screen >> test .out
echo 第一个学号错误，第二个正确 >> test.out
作业相似度匹配参数解析.exe 123456 1234567 test.cpp 80 screen >> test .out
echo 第一个学号错误，第二个正确 >> test.out
作业相似度匹配参数解析.exe 123456A 1234567 test.cpp 80 screen >> test .out
echo 第一个学号错误，第二个正确 >> test.out
作业相似度匹配参数解析.exe 12356A 1234567 test.cpp 80 screen >> test .out
echo 第一个学号错误，第二个错误 >> test.out
作业相似度匹配参数解析.exe 12356 12367 test.cpp 80 screen >> test .out
echo 第一个学号错误，第二个错误 >> test.out
作业相似度匹配参数解析.exe 123AAAA 12367AA test.cpp 80 screen >> test .out
echo 第一个学号错误，第二个错误 >> test.out
作业相似度匹配参数解析.exe 123AAAA 1236722 test.cpp 80 screen >> test .out
echo 第一个学号错误，第二个错误 >> test.out
作业相似度匹配参数解析.exe 1232323 12367AA test.cpp 80 screen >> test .out
echo 输入错误,其他正确 >> test.out
作业相似度匹配参数解析.exe 1232323 1236711 dffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff.cpp 80 screen >> test .out
echo 输入错错误,学号错误 >> test.out
作业相似度匹配参数解析.exe 12323 1236711 dffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff.cpp 80 screen >> test .out
echo 输入错误,学号错误 >> test.out
作业相似度匹配参数解析.exe 1232323 16711 dffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff.cpp 80 screen >> test .out
echo 输入错误,学号错误 >> test.out
作业相似度匹配参数解析.exe 1232323 16711ss dffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff.cpp 80 screen >> test .out
echo 输出错误,学号正确 >> test.out
作业相似度匹配参数解析.exe 1232323 1671123 fff.cpp 80 scredsffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffen >> test .out
echo 输出错误,学号错误 >> test.out
作业相似度匹配参数解析.exe 1232323 16711ss fff.cpp 80 scredsffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffen >> test .out
echo 正确，但是参数范围不正确 >> test.out
作业相似度匹配参数解析.exe 1234567 1234567 test.cpp -100 screen >> test .out
echo 正确，但是参数范围不正确 >> test.out
作业相似度匹配参数解析.exe 1234567 1234567 test.cpp 10 screen >> test .out
echo 正确，但是参数范围不正确 >> test.out
作业相似度匹配参数解析.exe 1234567 1234567 test.cpp 9100 screen >> test .out





