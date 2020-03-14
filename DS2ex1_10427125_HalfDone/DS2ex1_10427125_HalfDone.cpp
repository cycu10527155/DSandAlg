// 資訊四甲 10427125 庾琁 
 
#include <iostream>                                                         // cout, endl
#include <fstream>                                                          // open, is_open
#include <string>                                                           // string
#include <vector>                                                           // vector
#include <cstdlib>                                                          // atoi, system
#include <iomanip>                                                          // setw
#include <math.h>
#define nRecords    20                                                      // amount of display on screen

using namespace std;

typedef struct cT                                                           // declare a type for a selected record
{   string	cname;                                                          // college name
    string  dname;                                                          // department name
   	string  type;                                                           // either day or night
    string  level;                                                          // graduate or undergraduate
    int     total;                                                          // number of students                                                         // total
}	collegeType;
//*********************** ********************************************************************/

typedef struct hT											                // declare a type for a heap node
{	int	rid;                                                                // a serial number as record identifier
	int value;                                                              // the key for comparisons
}	heapType;


void heapInsert(heapType [], const int, const int, const int);              // insert one record into heap
void mission2();
void Add(string filename, int count);
//*********************** ********************************************************************/

int main(void)
{   fstream     inFile;                                                     // input file handler
    string      fileName;                                                   // name of input file
  string mission = "\0" ;
  while ( mission.compare("0") ){
  cout << "\n" ;
  cout << "************************\n" ;
  cout << "* Missions List        *\n" ; 
  cout << "* 0. Quit              *\n" ;
  cout << "* 1. Build a max heap  *\n" ;
  cout << "* 2. Build a DEAP      *\n" ;
  cout << "************************\n" ;
  cout << "\n" ;
  cout << "input a choose of mission(0, 1, 2)\n" ;
  cin >> mission ;
  if ( mission.length() != 1 || ( mission.at(0) - '0' < 0 || mission.at(0) - '0' > 2) ) {
  	cout << "Mission does not exist!\n" ;
  }
  else if ( mission.at(0) == '1' ) { //執行完畢要初始化
    do
    {   cout << endl << "Input the file name: [0]Quit" << endl;  // press 0 to stop execution
        cin >> fileName;
        if (!fileName.compare("0"))                                         // No file to open, so quit
            return 0;
        fileName += ".txt";                                                 // append a file extension
        inFile.open(fileName.c_str(), fstream::in);                         // open a file
        if (!inFile.is_open())
            cout << endl << "### " << fileName << " does not exist! ###" << endl;   // failed to open a file, so try again
        else
            break;                                                          // successfully open a file, so leave the loop
    } while(1);   //end while
    do
    {   string                  coName, depName, stLevel, coType;           // user-specified keywords for each field
        string                  quitOrNot;                                  // do it again or not
        char                    rBuf[255];                                  // buffer to keep one whole record
        vector <collegeType>     cSet;                                       // a collection of selected records
        int                     ansNo = 0;                                  // a serial number

        inFile.ignore(255,'\n');                                            // skip the first three line in file
        inFile.ignore(255,'\n');                                            // because they are file header
        inFile.ignore(255,'\n');                                            // indicates meta-data such as field names
        while (inFile.getline(rBuf, 255, '\n'))                             // retrieve one entire record from file
        {   string      temp;                                               // duplicate a string in another format
            collegeType oneC;                                               // keep one record with only the required fields
            int         cNo = 0, pre = 0, pos = 0;                          // indicators to extract each field in a record from left to right

            temp.assign(rBuf);                                              // make a duplicate of the entire record
            pos = temp.find_first_of('\t', pre);                            // move to the end of the first field
            while (pos != string::npos)
            {   switch (++cNo)
               	{   case 2: oneC.cname = temp.substr(pre, pos - pre);       // copy a college name
                            if ((coName != "*") && ((oneC.cname.find(coName)) == string::npos))
                                cNo = 0;
                            break;
                    case 4: oneC.dname = temp.substr(pre, pos - pre);       // copy a department name
                            if ((depName != "*") && ((oneC.dname.find(depName)) == string::npos))
                                cNo = 0;
                            break; 
                    case 5: oneC.type = temp.substr(pre, pos - pre);       // copy either day or night
                            if ((coType != "*") && ((oneC.type.find(coType)) == string::npos))
                                cNo = 0;
                            break; 
                    case 6: oneC.level = temp.substr(pre, pos - pre);       // copy graduate or undergraduate
                            if ((stLevel != "*") && ((oneC.level.find(stLevel)) == string::npos))
                                cNo = 0;
                            break;   
                   case 9:
                           oneC.total = atoi (temp.substr(pre, pos - pre).c_str() );       // copy a college name
                           if ( temp.substr(pre, pos - pre) == "-" )
                             cNo = 0;
                            break;
               	}   //end switch
               	if (cNo == 0)                                               // ignore a record if any field is not matched or unknown
                    break;
                 pre = ++pos;
                 pos = temp.find_first_of('\t', pre);                       // move to the end of the next field
            }   //end for*/
            if (cNo != 0)
                cSet.push_back(oneC);                                       // put a record into the collection if it is not ignored
        }   //end while
        inFile.close();   
		


        int len = cSet.size() - 1;
        
		for(int i=0 ; i<=len ; i++){
          cout << cSet[i].cname <<"\n"<<  cSet[i].dname  <<"\n"<< cSet[i].type<< "\n"<< cSet[i].level <<"\n"<< cSet[i].total <<"\n"<< endl;
        }
        
        
        if (!cSet.size())
            cout << endl << "### " << " There is nothing matched! ###" << endl;
        else
        {   try
            {   heapType	*heapArray = new heapType [cSet.size()];        // dynamic array to keep heap nodes, total size is known
                int         idx = 0;    
				 
				double temp = cSet.size()-1;   
				double level = 0;
				while(temp >= 2){
					level++;
					temp = temp/2;				
				}				                                
                int leftmost = pow(2,level)-1;         // find leftmost

                for (vector<collegeType>::iterator it = cSet.begin(); it < cSet.end(); ++idx, ++it)
                    heapInsert(heapArray, idx, it->total, idx);             // serial number is also the current bottom in the heap
                    
                cout << endl << setw(3) << "<max heap>" << endl;
				cout << "root: [" << heapArray[0].rid+1 << "] " << heapArray[0].value << endl;
				cout << "bottom: [" << heapArray[cSet.size()-1].rid+1 << "] " << heapArray[cSet.size()-1].value << endl;             // display the root and bottom in the resultant heap
                cout << "leftmost: [" << heapArray[leftmost].rid+1 << "]" << heapArray[leftmost].value << endl;
                
            for(int i=0 ; i<=len ; i++){
              cout << heapArray[i].rid+1  <<"\n"<<   heapArray[i].value <<"\n"<< "level:"<<level<<  endl;
            }
                
                
                delete [] heapArray;				                        // release the dynamic array of heap structure
            }	// end try
            catch (std::bad_alloc& ba)								        // failed to allocate dynamic space
            {
                std::cerr << endl << "bad_alloc caught: " << ba.what() << endl;
            }   // end catch
            cSet.clear();                                                   // release the space of vector for the selected records
        }   // end else
        cout << endl << "[0]Quit or [Any other]continue?" << endl;
        cin >> quitOrNot;
        if (!quitOrNot.compare("0"))                                        // press 0 to stop execution
            return 0;
        else
            inFile.open(fileName.c_str(), fstream::in);                     // open a file
    } while (1);
  }
  else if ( mission.at(0) == '2' ){ //執行完畢要初始化 
    mission2() ;
    }  
  } 
}	// end main
//*********************** ********************************************************************/

void heapInsert(heapType H[], const int newRid, const int newValue, const int bottom)
{   // a heap, serial number of a new record, key for comparisons on a heap, the bottom node
	int place = bottom;                                                     // start at the bottom node
    int parent = ( place - 1 )/2;										        // locate its parent node

	H[place].rid = newRid;                                                  // save a new record to the bottom node
	H[place].value = newValue;



	do {
    if ( H[place].value < H[parent].value ) {
      swap( H[parent],H[place] );                    //change H[parent],H[place] 
	  place = parent;        
      parent = ( place - 1 ) / 2;						//RESET PLACE AND PARENT 				       
    }
    else place = -1 ;
	    
  } while ( place != -1 ) ;

}	// end heapInsert
//*********************** ********************************************************************/

/*void minheapInsert(heapType H[], const int newRid, const int newValue, const int bottom)
{   // a heap, serial number of a new record, key for comparisons on a heap, the bottom node
	int place = bottom;                                                     // start at the bottom node
    int parent = ( place - 1 )/2;										        // locate its parent node

	H[place].rid = newRid;                                                  // save a new record to the bottom node
	H[place].value = newValue;
      
	  do {
    if ( H[place].value > H[parent].value ) {
      swap( H[parent],H[place] );                    //change H[parent],H[place] 
	  place = parent;        
      parent = ( place - 1 ) / 2;						//RESET PLACE AND PARENT 				       
    }
    else place = -1 ;
	    
  } while ( place != -1 ) ;

}	// end heapInsert
//*********************** ********************************************************************/

void mission2() {
    fstream File;
	string input ;
	cout << "Please enter the filename or 0 to quit\n" ;
	cin >> input ;
	string filename ;
	filename = "input" + input + ".txt" ;
	FILE *pFile ;
	string tmpp ;
	int count = 0 ;
//	File.open(filename.c_str());
	pFile = fopen(filename.c_str(),"a");
	while ( File == NULL && input != "0" ) {  // 開啟檔案 
		cout << "input" << input << ".txt does not exist!!!\n\n" ;
		cout << "Please enter the filename or 0 to quit\n" ;
	    cin >> input ;
	    if ( input == "0" )
	      break;
	    filename = "input" + input + ".txt" ;
	    pFile = fopen(filename.c_str(),"a");
//		File.open(filename.c_str());
	}
		
	fprintf(pFile,"\n");
	fclose(pFile);
	File.open(filename.c_str());
    getline(File,tmpp);  //先把第一行讀掉 
    getline(File,tmpp);  
    getline(File,tmpp);  
//    cout << tmpp ;
    while(!File.eof()) {
      getline(File,tmpp); 
      count++;
    } 
    
	  File.close();
	  count = count - 2 ;
//      cout<< count ;
      Add(filename, count);
  } // mission1()
  
  void Add(string filename, int count) {
  	count++;
  	int count1 = 0 ;
  	bool change = false ;
  	int *heap = new int [count];
  	int *num = new int [count];
  	int cur = 0 ; // current
  	for ( int i = 0 ; i < count ; i++)
  	  heap[i] = -1 ;
  	cur++;
  	int last = cur ;
  	int parent = cur ;
  	int level = 0 ;
  	string tmpp;
    fstream File;
	File.open(filename.c_str());
    getline(File,tmpp);  //先把第一行讀掉 
    getline(File,tmpp);  
    getline(File,tmpp);  
    while(!File.eof() && count1 < count ) {
      int a = 0 ;
      cur = last ;
      last++ ;
      getline(File,tmpp,'\t'); 
      getline(File,tmpp,'\t'); 
      getline(File,tmpp,'\t'); 
      getline(File,tmpp,'\t'); 
      getline(File,tmpp,'\t'); 
      getline(File,tmpp,'\t');
      getline(File,tmpp,'\t'); 
      a = atoi(tmpp.c_str());
      heap[cur] = a ;
      num[cur] = count1 + 1 ;
      getline(File,tmpp,'\t'); 
      getline(File,tmpp,'\t'); 
      getline(File,tmpp,'\t');
      parent = cur ;
      if ( cur != 1 && cur != 2 ){
      	parent = cur ;
        while ( parent != 1 && parent != 2 ){ // 判斷在左子樹還是右子樹 
      	  parent = ( parent - 1 ) / 2 ;
	    } // while
	  }
	  
	  if ( parent == 1 ) { // 目前節點在左子樹 
	  	level = log((cur+1))/log(2);
	  	if ( cur+(int)pow(2,level-1) < last ){ // 有相對應節點 
	  	  if ( heap[cur] > heap[cur+(int)pow(2,level-1)] ) { // 左比右大 交換 
	  	    int temp = heap[cur] ;
			heap[cur] = heap[cur+(int)pow(2,level-1)];
			heap[cur+(int)pow(2,level-1)] = temp ; // swap
	  	    temp = num[cur] ;
			num[cur] = num[cur+(int)pow(2,level-1)];
			num[cur+(int)pow(2,level-1)] = temp ; // swap
			cur = cur+(int)pow(2,level-1);
			change = true ;
		  } // 左比右大 交換 
	    } //if()判斷是否有相對應節點 
	    else { // 沒有相對應節點
		  if ( heap[cur] > heap[((cur+(int)pow(2,level-1))-1 ) / 2] && heap[((cur+(int)pow(2,level-1))-1 ) / 2] != -1 ) { //是否比相對應節點的父節點還要大
	        int temp = heap[cur];
	        heap[cur] = heap[((cur+(int)pow(2,level-1)) -1 ) / 2] ;
	        heap[(cur+(int)pow( 2, level - 1 ) -1 ) / 2 ] = temp ; //swap
	        temp = num[cur];
	        num[cur] = num[((cur+(int)pow(2,level-1)) -1 ) / 2] ;
	        num[(cur+(int)pow( 2, level - 1 ) -1 ) / 2 ] = temp ; //swap
	        cur = (cur+(int)pow(2,level-1) -1) / 2 ;
	        change = true ;
		  } // if ()是否比相對應父節點大 
		} // 沒有相對應節點 
		
	    parent = ( cur - 1 ) / 2 ;
	    
	    if ( !change ) {
	      while ( heap[parent] != -1 && heap[cur] < heap[parent] ) { // 是否還有父節點&是否比父節點小 
	        int temp = heap[cur] ;
	        heap[cur] = heap[parent] ;
	        heap[parent] = temp ; // swap
	        temp = num[cur] ;
	        num[cur] = num[parent] ;
	        num[parent] = temp ; // swap
	        cur = parent ;
	        parent = ( cur - 1 ) / 2 ;
		  } // while()
	    } // if (!change) 沒交換
		else {
		  while ( heap[parent] != -1 && heap[cur] > heap[parent] ) { // 是否還有父節點&是否比父節點大 
	      int temp = heap[cur] ;
	      heap[cur] = heap[parent] ;
	      heap[parent] = temp ; // swap
	      temp = num[cur] ;
	      num[cur] = num[parent] ;
	      num[parent] = temp ; // swap
	      cur = parent ;
	      parent = ( cur - 1 ) / 2 ;
		  } // while()
		} // 有交換 
      } // if() 目前節點在左子樹
      
      else if ( parent == 2 ) { // 目前節點在右子樹 
	  	level = log((cur+1))/log(2);
	  	if ( heap[cur-(int)pow(2,level-1)] != -1 ) {  // 有相對應節點 
	  		if ( heap[cur] < heap[cur-(int)pow(2,level-1)] ) { // 右比左小 
	  			int temp = heap[cur];
	  			heap[cur] = heap[cur-(int)pow(2,level-1)];
	  			heap[cur-(int)pow(2,level-1)] = temp ;
	  			temp = num[cur];
	  			num[cur] = num[cur-(int)pow(2,level-1)];
	  			num[cur-(int)pow(2,level-1)] = temp ;
	  			cur = cur-(int)pow(2,level-1) ;
	  			change = true ;
			  } // 右比左小 交換 
		  } // if() 判斷是否有相對應節點
		  
		  /*********************************
	    else{ // 沒有相對應節點 
	      if ( heap[cur] < heap[(cur-(int)pow(2,level-1)-1)/2] && heap[(cur-(int)pow(2,level-1)-1)/2] != -1 ) { // 是否比相對應節點的父節點還要小
	        int temp = heap[cur];
	        heap[cur] = heap[(cur-(int)pow(2,level-1)-1)/2] ;
	        heap[(cur-(int)pow(2,level-1)-1)/2] = temp ;
	        cur = (cur-(int)pow(2,level-1)-1)/2 ;
		  } // if()比相對應父節點小就交換 
		} // else()沒有相對節點 
		************************************/
		
	    parent = ( cur - 1 ) / 2 ;
	    if ( !change ) {
	      while ( heap[parent] != -1 && heap[cur] > heap[parent] ) { // 是否還有父節點&是否比父節點大 
	        int temp = heap[cur] ;
	        heap[cur] = heap[parent] ;
	        heap[parent] = temp ; // swap
	        temp = num[cur] ;
	        num[cur] = num[parent] ;
	        num[parent] = temp ; // swap
	        cur = parent ;
	        parent = ( cur - 1 ) / 2 ;
		  } // while()
	    } // if (!change) 沒交換
		else {
		  while ( heap[parent] != -1 && heap[cur] < heap[parent] ) { // 是否還有父節點&是否比父節點小 
	      int temp = heap[cur] ;
	      heap[cur] = heap[parent] ;
	      heap[parent] = temp ; // swap
	      temp = num[cur] ;
	      num[cur] = num[parent] ;
	      num[parent] = temp ; // swap
	      cur = parent ;
	      parent = ( cur - 1 ) / 2 ;
		  } // while()
		} // 有交換
	  } // if() 目前節點在右子樹 
	  change = false ;
	  count1++;
  } // while(EOF) 讀完了 

  level = log((count+1))/log(2);
  int leftmost = (int)pow(2,level)-1;
  cout << "<DEAP>" << "\n" ;
  cout << "bottom: [" << num[count-1] << "] " << heap[count-1] << "\n";
  cout << "leftmost bottom: [" << num[leftmost] << "] " << heap[leftmost];
//  for ( int i = 0 ; i < count ; i++)
//    cout << num[i] << "\n" ;
//cout << count ;
} // Add() 
