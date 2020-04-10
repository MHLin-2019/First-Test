/*
Image processing: ppm image
Read file, write file, struct
Author: 10832113林明樺 Ming-Hua Lin
Date: 20191114
*/

#include <iostream>
#include <fstream>
using namespace std;

#define HIGHT 4500
#define WIDTH 4500



//宣告函式(基礎檔案處理函式)
void openfile();
void readimage();
void choose();
void writeimage();
void closefile();
//宣告函式(濾鏡函式)
void converter_BGR();
void hope();
void lighter();
void darker();
void gray();
void Orange_Yellow();
void red();
void m3();
void m5();
void g3();
void g5();
void g7();
void cube1();
void cube2();
void seperate();



//自訂像素結構
struct PIXEL{
    int R;
    int G;
    int B;
};



//影像紀錄
PIXEL image1[HIGHT][WIDTH]; //記錄原始影像
PIXEL image2[HIGHT][WIDTH]; //記錄處理後影像
PIXEL imagecopy[HIGHT+2][WIDTH+2];



//所需數字宣告
fstream fin;   //記錄輸入檔案流
fstream fout; //記錄輸出檔案流
char type[5]; //記錄影像形態 p3,p6
int row, col; //記錄影像大小
int mode;      //記錄色彩模型 255為 0-255，指256色
//模糊化需用
int m_kernel3[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
int g_kernel3[3][3] = {{1,2,1},{2,4,2},{1,2,1}};
int m_kernel5[5][5] = {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}};
int g_kernel5[5][5] = {{2,7,12,7,2},{7,31,52,31,7},{12,52,127,52,12},{7,31,52,31,7},{2,7,12,7,2}};
int g_kernel7[7][7] = {{1,1,2,2,2,1,1},{1,3,4,5,4,3,1},{2,4,7,8,7,4,2},{2,5,8,10,8,5,2},{2,4,7,8,7,4,2},{1,3,4,5,4,3,1},{1,1,2,2,2,1,1}};
	//特效組合需用
int rate1;
int rate2;
int area; // 1為左 2為右



//主程式
int main()
{
	int anotherimage=1;
	int anotherstyle=1;

	while(anotherimage){
		openfile();
		readimage();

		while(anotherstyle){
			choose();
			writeimage();
            closefile();
			//是否繼續處理此圖
				cout << "想對此圖片進行其他特效嗎?(1.想, 0.不想)" << endl;
				cin >> anotherstyle;
		}
		//是否繼續執行此程式
			cout << "想對其他圖片進行處理嗎?(1.想, 0.不想)" << endl;
			cin >> anotherimage;
	}

	return 0;
}

//開啟檔案
void openfile()
{
    char infile[20];
    cout << "Input your filename (ex: original.ppm, lena.ppm... ):";
    cin >> infile;

    cout << "program running..." << endl;
    fin.open(infile, ios::in); //open input file   ex: original.ppm, lena.ppm,.....

    if(!fin)
        cout<< "Fail to open file! Please close the window." << endl;

}

//讀檔案
void readimage()
{
    fin >> type;
    fin >> col >> row;
    fin >> mode;

    for (int i=0; i<row; i++)
        for (int j=0; j<col; j++)
            fin >> image1[i][j].R >> image1[i][j].G >> image1[i][j].B ;

    cout << "Image size:" << col << " x "  << row << endl;
    cout << "Read Image Successfully!" << endl;
}

void choose()
{
	int style1; //特效種類編號
	int style2; //各組特效編號
	int style3; //最精確的編號(不是每個style1都會用到)

	//特效類別選單
	cout << "請選擇一種特效類別" << endl;
	cout << "1.顏色處理" << endl;
	cout << "2.模糊" << endl;
	cout << "3.馬賽克" <<endl;
	cout << "4.特效組合" << endl;

	//使用者特效類別選擇
	cout << endl << "我選擇的特效類別為: ";
	cin >> style1;
	cout << endl;

	//執行特效類別選擇
	switch(style1){
		case 1:
			//顏色處理選單
			cout << "顏色處理選單:" << endl;
			cout << "1.色彩互換" << endl;
			cout << "2.偏橘色調" << endl;
			cout << "3.增亮" << endl;
			cout << "4.變暗" << endl;
			cout << "5.灰階" << endl;
			cout << "6.二值化(橘黃) ps: 三思，檔案太大跑不動" << endl;
			cout << "7.偏紅(復古風)" << endl;

			//使用者顏色處理選擇
			cout << endl << "我選擇的特效為: ";
			cin >> style2;
			cout << endl;

			//執行顏色處理選擇
			switch(style2){
				case 1:
					converter_BGR();
					break;
				case 2:
					hope();
					break;
				case 3:
					lighter();
					break;
                case 4:
                    darker();
                    break;
				case 5:
					gray();
					break;
				case 6:
					Orange_Yellow();
					break;
				case 7:
					red();
					break;
			}
			break;

		case 2:
			//模糊種類選單
			cout << "模糊種類選單:"  << endl;
			cout << "	(選擇後會進入下一層選單)" << endl;
			cout << "1.普通模糊" << endl;
			cout << "2.高斯模糊" << endl;

			//使用者模糊種類選擇
			cout << endl << "我選擇的種類為: ";
			cin >> style2;
			cout << endl;

			//執行模糊種類選擇
			switch(style2){
				case 1:
					//普通模糊選單
					cout << "普通模糊選單" << endl;
					cout << "1. 3x3" << endl;
					cout << "2. 5x5" << endl;

					//使用者普通模糊選擇
					cout << endl << "我選擇的特效為: ";
					cin >> style3;
					cout << endl;

					//執行普通模糊選擇
					switch(style3){
						case 1:
							m3();
							break;
						case 2:
							m5();
							break;
					}
                break;

				case 2:
					//高斯模糊選單
					cout << "高斯模糊選單" << endl;
					cout << "1. 5x5" << endl;
					cout << "2. 7x7" << endl;

					//使用者高斯模糊選擇
					cout << endl << "我選擇的特效為: ";
					cin >> style3;
					cout << endl;

					//執行高斯模糊選擇
					switch(style3){
						case 1:
							g5();
							break;
						case 2:
							g7();
							break;
					}
					break;
			}
        break;

		case 3:
			//馬賽克選單
			cout << "馬賽克選單:" << endl;
			cout << "1. 7x7" << endl;
			cout << "2. 15x15" << endl;

			//使用者馬賽克選擇
			cout << endl << "我選擇的特效為: ";
			cin >> style2;
			cout << endl;

			//執行馬賽克選擇
			switch(style2){
				case 1:
					cube1();
					break;
				case 2:
					cube2();
					break;
			}
			break;

		case 4:
			//特效組合說明
			cout << "特效組合說明:" << endl;
			cout << "	此特效組合會將圖片在橫方向分開，並在分開後將兩種組合套入，一為變暗，一為增亮。" << endl;

			//特效分割選擇
			cout << "分割方式有兩種選擇" << endl;
			cout << "1.用一條鉛直線分開" << endl;
			cout << "2.用兩條鉛直線分開" << endl;

			//使用者特效分割選擇
			cout << endl << "我選擇的分割方式為: ";
			cin >> style2;
			cout << endl;
			switch(style2){
				case 1:
					cout << "請輸入分割比例 Ex: 70 (左邊占百分之70)" << endl;
					cin >> rate1;

					//增亮選單
					cout << "請選擇增亮部分" << endl;
					cout << "1.左半" << endl;
					cout << "2.右半" << endl;

					//使用者增亮選擇
					cout << "我選擇的部分為: " << endl;
					cin >> area;
					cout << endl;

					//執行濾鏡
					seperate();
					break;

				case 2:
					cout << "增亮部分已預設為中間" << endl;
					cout << "請輸入第一條線左邊所佔之比例、第二條線左邊所佔之比例 Ex: 20 80 (鉛直方向分三段，三段比例為 1:3:1)" << endl;
					cin >> rate1 >> rate2;
					seperate();//執行濾鏡
					break;
			}
			break;
	}
}

//寫入檔案
void writeimage()
{
    char outfile[20];
    cout << "Input your  Output filename (ex: original_gray.ppm, lena_gray.ppm... ):";
    cin >> outfile;             // ex: original_gray.ppm, lena_gray.ppm

    fout.open(outfile, ios::out); //open output file
    fout << type << endl;
    fout << col << " " << row << endl;
    fout << mode << endl;

    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
            fout << image2[i][j].R << " " << image2[i][j].G << " " << image2[i][j].B << " ";
        fout << endl;
    }

    cout << "Write Image Successfully!!"  << endl;

}

//關閉檔案
void closefile()
{
    fin.close();  //close input file
    fout.close(); //close output file
}


//色彩互換
void converter_BGR(){
    for( int i = 0 ; i < row ; i++ )
        for( int j = 0 ; j < col ; j++ ){
            image2[i][j].R = image1[i][j].B;
            image2[i][j].G = image1[i][j].G;
            image2[i][j].B = image1[i][j].R;
        }
}

//偏橘色調
void hope()
{
    for( int i = 0 ; i < row ; i++ )
    {
        for( int j = 0 ; j < col ; j++ )
        {
            if(image1[i][j].R*0.299 <= 255)
                image2[i][j].R = image1[i][j].R;
            if(image1[i][j].G*0.587 <= 255)
                image2[i][j].G = image1[i][j].G;
        }
    }
}

//增亮
void lighter()
{
    for(int i=0 ; i<row ; i++)
        for(int j=0 ; j<col ; j++)
        {
            if(image1[i][j].R*1.2 <= 255)
                image2[i][j].R = image1[i][j].R* 1.2;
            else
                image2[i][j].R = 255;
            if(image1[i][j].G*1.2 <= 255)
                image2[i][j].G = image1[i][j].G * 1.2;
            else
                image2[i][j].G = 255;
            if(image1[i][j].B*1.2 <= 255)
                image2[i][j].B = image1[i][j].B * 1.2;
            else
                image2[i][j].B = 255;
        }

}

//變暗
void darker()
{
    for(int i=0 ; i<row ; i++)
        for(int j=0 ; j<col ; j++){
            image2[i][j].R = image1[i][j].R / 1.5;
            image2[i][j].G = image1[i][j].G / 1.5;
            image2[i][j].B = image1[i][j].B / 1.5;
        }
}

//灰階化
void gray()
{
    for( int i = 0 ; i < row ; i++ )
    {
        for( int j = 0 ; j < col ; j++ )
        {
            int g;
            g = image1[i][j].R*0.299 + image1[i][j].G*0.587 +image1[i][j].B*0.114;
            image2[i][j].R = g;
            image2[i][j].G = g;
            image2[i][j].B = g;
        }
    }
}

//二值化 Orange_Yellow
void Orange_Yellow()
{
    int g[row][col]; //存放g值的陣列
	int gsum; //g值總和
	int gaverage; //g值平均
	int theshold; //二值化門檻值
	int bigger; //g值比平均g值大的像素數
	int smaller; //g值比平均g值小的像素數
	int d; //g值比平均g值大的像素數和比平均g值想的像素數之差

	//儲存每個像素的位置及其g值
	for(int i=0 ; i<row ; i++)
		for(int j=0 ; j<col ; j++){
			g[i][j] = image1[i][j].R*0.299 + image1[i][j].G*0.587 +image1[i][j].B*0.114;
			gsum += g[i][j];
		}
    cout << "image processing" << endl;

	//g值比平均g值大的像素數和比平均g值想的像素數之差
	gaverage = gsum / ( row * col );
	for(int i=0 ; i<row ; i++)
		for(int j=0 ; j<col ; j++){
			if(g[i][j]>gaverage)
				bigger++;
			else if(g[i][j]<gaverage)
				smaller++;
		}
	d = bigger - smaller;

	//設定門檻值
	if( gaverage + gaverage * d / ( row * col ) < 255 )
		theshold = gaverage * ( 1 + d / ( row * col ) * 10);
	else
		theshold = gaverage;

	//二值化
	for(int i=0 ; i<row ; i++)
		for(int j=0 ; j<col ; j++){
			if(g[i][j]<theshold)
            {
                image2[i][j].R = 255;
                image2[i][j].G = 97;
                image2[i][j].B = 0;
            }
            else
            {
                image2[i][j].R = 255;
                image2[i][j].G = 208;
                image2[i][j].B = 68;
            }
		}
}

//偏單色化 紅
void red()
{
    //算平均亮度
    int R=0;
    int G=0;
    int B=0;
    for ( int i = 0 ; i < row ; i++ )
    {
        for( int j = 0 ; j < col ; j++ )
        {
            R += image1[i][j].R;
            G += image1[i][j].G;
            B += image1[i][j].B;
        }
    }
    int L = R*.299 + G*.587 + B*.114 / (row*col);

    //圖片轉換
    for( int i = 0 ; i < row ; i++ )
    {
        for( int j = 0 ; j < col ; j++ )
        {
            int r;
            r = image1[i][j].R*.299 + image1[i][j].G*.587 +image1[i][j].B*.114;
            image2[i][j].R = r;
            image2[i][j].G = r*.587;
            image2[i][j].B = r*.114;
        }
    }
}

//普通模糊3x3
void m3()
{
    for(int i = 0 ; i < row+2 ; i++ )
    {
        for(int j = 0 ; j < col+2 ; j++ )
        {
            imagecopy[i][j].R=0;
            imagecopy[i][j].G=0;
            imagecopy[i][j].B=0;
        }
    }
    for(int i = 1 ; i < row+1 ; i++ )
    {
        for(int j = 1 ; j < col+1 ; j++ )
        {
            imagecopy[i][j].R=image1[i-1][j-1].R;
            imagecopy[i][j].G=image1[i-1][j-1].G;
            imagecopy[i][j].B=image1[i-1][j-1].B;
        }
    }

    for(int i = 1 ; i < row+1 ; i++ )
    {
        for(int j = 1 ; j < col+1 ; j++)
        {
            for( int p = -1 ; p < 2 ; p++ )
            {
                for(int q = -1 ; q < 2 ; q++ )
                {
                    image2[i-1][j-1].R += imagecopy[i+p][j+q].R*m_kernel3[p+1][q+1];
                    image2[i-1][j-1].G += imagecopy[i+p][j+q].G*m_kernel3[p+1][q+1];
                    image2[i-1][j-1].B += imagecopy[i+p][j+q].B*m_kernel3[p+1][q+1];

                }
            }

            image2[i-1][j-1].R /= 9;
            image2[i-1][j-1].G /= 9;
            image2[i-1][j-1].B /= 9;
        }
    }

}

//普通模糊5x5
void m5()
{
    for(int i = 0 ; i < row+4 ; i++ )
    {
        for(int j = 0 ; j < col+4 ; j++ )
        {
            imagecopy[i][j].R=0;
            imagecopy[i][j].G=0;
            imagecopy[i][j].B=0;
        }
    }

    for(int i = 2 ; i < row+2 ; i++ )
    {
        for(int j = 2 ; j < col+2 ; j++ )
        {
            imagecopy[i][j].R=image1[i-2][j-2].R;
            imagecopy[i][j].G=image1[i-2][j-2].G;
            imagecopy[i][j].B=image1[i-2][j-2].B;
        }
    }

    for(int i = 2 ; i < row+1 ; i++ )
    {
        for(int j = 2 ; j < col+1 ; j++)
        {
            for( int p = - 2; p < 3 ; p++ )
            {
                for(int q = -2 ; q < 3 ; q++ )
                {
                    image2[i-2][j-2].R += imagecopy[i+p][j+q].R*m_kernel5[p+2][q+2];
                    image2[i-2][j-2].G += imagecopy[i+p][j+q].G*m_kernel5[p+2][q+2];
                    image2[i-2][j-2].B += imagecopy[i+p][j+q].B*m_kernel5[p+2][q+2];

                }
            }

            image2[i-2][j-2].R /= 25;
            image2[i-2][j-2].G /= 25;
            image2[i-2][j-2].B /= 25;
        }
    }

}

//高斯模糊5x5
void g5()
{
    for(int i = 0 ; i < row+4 ; i++ )
    {
        for(int j = 0 ; j < col+4 ; j++ )
        {
            imagecopy[i][j].R=0;
            imagecopy[i][j].G=0;
            imagecopy[i][j].B=0;
        }
    }
    for(int i = 2 ; i < row+2 ; i++ )
    {
        for(int j = 2 ; j < col+2 ; j++ )
        {
            imagecopy[i][j].R=image1[i-2][j-2].R;
            imagecopy[i][j].G=image1[i-2][j-2].G;
            imagecopy[i][j].B=image1[i-2][j-2].B;
        }
    }

    for(int i = 2 ; i < row+2 ; i++ )
    {
        for(int j = 2 ; j < col+2 ; j++)
        {
            for( int p = - 2; p < 3 ; p++ )
            {
                for(int q = -2 ; q < 3 ; q++ )
                {
                    image2[i-2][j-2].R += imagecopy[i+p][j+q].R*g_kernel5[p+2][q+2];
                    image2[i-2][j-2].G += imagecopy[i+p][j+q].G*g_kernel5[p+2][q+2];
                    image2[i-2][j-2].B += imagecopy[i+p][j+q].B*g_kernel5[p+2][q+2];

                }
            }

            image2[i-2][j-2].R /= 571;
            image2[i-2][j-2].G /= 571;
            image2[i-2][j-2].B /= 571;
        }
    }

}

//高斯模糊7x7
void g7()
{
    for(int i = 0 ; i < row+6 ; i++ )
        for(int j = 0 ; j < col+6 ; j++ )
        {
            imagecopy[i][j].R=0;
            imagecopy[i][j].G=0;
            imagecopy[i][j].B=0;
        }

    for(int i = 3 ; i < row+3 ; i++ )
        for(int j = 3 ; j < col+3 ; j++ )
        {
            imagecopy[i][j].R=image1[i-3][j-3].R;
            imagecopy[i][j].G=image1[i-3][j-3].G;
            imagecopy[i][j].B=image1[i-3][j-3].B;
        }

    for(int i = 3 ; i < row+3 ; i++ )
        for(int j = 3 ; j < col+3 ; j++)
        {
            for( int p = - 3; p < 4 ; p++ )
                for(int q = -3 ; q < 4 ; q++ )
                {
                    image2[i-3][j-3].R += imagecopy[i+p][j+q].R*g_kernel7[p+3][q+3];
                    image2[i-3][j-3].G += imagecopy[i+p][j+q].G*g_kernel7[p+3][q+3];
                    image2[i-3][j-3].B += imagecopy[i+p][j+q].B*g_kernel7[p+3][q+3];

                }

            image2[i-3][j-3].R /= 170;
            image2[i-3][j-3].G /= 170;
            image2[i-3][j-3].B /= 170;
        }


}

//馬賽克1
void cube1()
{
    for(int i=0 ; i<row ; i++)
        for(int j=0 ; j<col ; j++)
        {
            image2[i][j].R = 0;
            image2[i][j].G = 0;
            image2[i][j].B = 0;
        }

    for(int i=3 ; i<row ; i+=7)
    {
        for(int j=3 ; j<col ; j+=7)
        {
            for(int p=-3 ; p<4 ; p++ )
                for(int q=-3 ; q<4 ; q++)
                {
                    image2[i][j].R += image1[i+p][j+q].R*g_kernel7[p+3][q+3];
                    image2[i][j].G += image1[i+p][j+q].G*g_kernel7[p+3][q+3];
                    image2[i][j].B += image1[i+p][j+q].B*g_kernel7[p+3][q+3];
                }

            image2[i][j].R /= 170;
            image2[i][j].G /= 170;
            image2[i][j].B /= 170;


            for(int p=-1 ; p<3 ; p++)
                for(int q=-1 ; q<3 ; q++)
                {
                    image2[i+p][j+q].R = image2[i][j].R;
                    image2[i+p][j+q].G = image2[i][j].G;
                    image2[i+p][j+q].B = image2[i][j].B;
                }
        }
    }
}

//馬賽克2
void cube2()
{
    for(int i=0 ; i<row ; i++)
        for(int j=0 ; j<col ; j++)
        {
            image2[i][j].R = 0;
            image2[i][j].G = 0;
            image2[i][j].B = 0;
        }

    for(int i=7 ; i<row ; i+=15)
        for(int j=7 ; j<col ; j+=15)
        {
            for(int p=-7 ; p<8 ; p++)
                for(int q=-7 ; q<8 ; q++)
                {
                    image2[i][j].R += image1[i+p][j+q].R;
                    image2[i][j].G += image1[i+p][j+q].G;
                    image2[i][j].B += image1[i+p][j+q].B;
                }

            image2[i][j].R /= 225;
            image2[i][j].G /= 225;
            image2[i][j].B /= 225;

            for(int p=-5 ; p<6 ; p++)
                for(int q=-5 ; q<6 ; q++)
                {
                    image2[i+p][j+q].R = image2[i][j].R;
                    image2[i+p][j+q].G = image2[i][j].G;
                    image2[i+p][j+q].B = image2[i][j].B;
                }
        }
}

//濾鏡組合
void seperate()
{
    if(rate2==0){
        if(area==1){
            for(int i=0 ; i<row ; i++)
                for(int j=0 ; j < col*rate1/100 ; j++){
                    if(image1[i][j].R*1.2 <= 255)
                        image2[i][j].R = image1[i][j].R* 1.2;
                    else
                        image2[i][j].R = 255;
                    if(image1[i][j].G*1.2 <= 255)
                        image2[i][j].G = image1[i][j].G * 1.2;
                    else
                        image2[i][j].G = 255;
                    if(image1[i][j].B*1.2 <= 255)
                        image2[i][j].B = image1[i][j].B * 1.2;
                    else
                        image2[i][j].B = 255;
                }
            for(int i=0; i<row ; i++)
                for(int j=col*rate1/100 ; j<col ; j++){
                    image2[i][j].R = image1[i][j].R / 1.5;
                    image2[i][j].G = image1[i][j].G / 1.5;
                    image2[i][j].B = image1[i][j].B / 1.5;
                }
        }
        else{
            for(int i=0 ; i<row ; i++)
                for(int j=0 ; j < col*rate1/100 ; j++){
                    image2[i][j].R = image1[i][j].R / 1.5;
                    image2[i][j].G = image1[i][j].G / 1.5;
                    image2[i][j].B = image1[i][j].B / 1.5;
                }
            for(int i=0 ; i<row ; i++)
                for(int j=col*rate1/100 ; j<col ; j++){
                    if(image1[i][j].R*1.2 <= 255)
                        image2[i][j].R = image1[i][j].R* 1.2;
                    else
                        image2[i][j].R = 255;
                    if(image1[i][j].G*1.2 <= 255)
                        image2[i][j].G = image1[i][j].G * 1.2;
                    else
                        image2[i][j].G = 255;
                    if(image1[i][j].B*1.2 <= 255)
                        image2[i][j].B = image1[i][j].B * 1.2;
                    else
                        image2[i][j].B = 255;
                }
        }
    }

    else{
        for(int i=0 ; i<row ; i++)
            for(int j=0 ; j<col*rate1/100 ; j++){
                image2[i][j].R = image1[i][j].R / 1.5;
                image2[i][j].G = image1[i][j].G / 1.5;
                image2[i][j].B = image1[i][j].B / 1.5;
            }
        for(int i=0 ; i<row ; i++)
            for(int j=col*rate1/100 ; j<col*rate2/100 ; j++){
                if(image1[i][j].R*1.2 <= 255)
                    image2[i][j].R = image1[i][j].R* 1.2;
                else
                    image2[i][j].R = 255;
                if(image1[i][j].G*1.2 <= 255)
                    image2[i][j].G = image1[i][j].G * 1.2;
                else
                    image2[i][j].G = 255;
                if(image1[i][j].B*1.2 <= 255)
                    image2[i][j].B = image1[i][j].B * 1.2;
                else
                    image2[i][j].B = 255;
        }
        for(int i=0 ; i<row ; i++)
            for(int j=col*rate2/100 ; j<col ; j++){
                image2[i][j].R = image1[i][j].R / 1.5;
                image2[i][j].G = image1[i][j].G / 1.5;
                image2[i][j].B = image1[i][j].B / 1.5;
            }
    }
}
