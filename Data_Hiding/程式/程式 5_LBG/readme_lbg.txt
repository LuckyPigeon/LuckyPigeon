此為 LBG algorithm 之實作程式  by 90321003 謝明龍

各檔案說明：

LBG\SOURCE\ 存放原始碼

    1. lbg.cpp  ............. 讀入 lenna.raw 檔，經 PNN & LBG algorithm 壓縮
                              成 *.lbg 檔 (含 codebook 及壓縮後的代碼)

    2. delbg.cpp  ........... 讀入 *.lbg 檔解壓縮成 *.raw 檔

LBG\VC\ 以 MS Virtual C++ compiler 2003 編譯後之執行檔
LBG\    以 Intel C++ compiler 8.1       編譯後之執行檔 (optimized for P4)

    1. lbg.exe  ............. 參數說明：LBG x.raw y.lbg epison

                                        讀入 x.raw 壓縮成 y.lbg，epison =
                                        連續兩次 distortion 之差異比值，為
                                        LBG 程式判斷 LBG algo 結束與否之標準

    2. delbg.exe  ........... 參數說明：DELBG y.lbg x.raw

                                        讀入 y.lbg 解壓縮成 x.raw

    3. lenna.raw  ........... 範例圖片

