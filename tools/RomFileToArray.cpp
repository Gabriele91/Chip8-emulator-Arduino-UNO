#include <cstdio>
#include <memory>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>

#define START_LOCATION 512
#define MEMORY_SIZE 4096
#define EXITERROR(s,i) { std::printf(s); while (getchar()==EOF); std::exit(i); };
unsigned char bfile[4096];
long size_buffer;

std::string getFileName(const char *n){
	
	const char* startbasenameUnixWindow=std::strrchr(n,'/');
	const char* startbasenameWindow=std::strrchr(n,'\\');

	const char* startbasename=startbasenameUnixWindow > startbasenameWindow ? 
										(startbasenameUnixWindow!=NULL ? 
													startbasenameUnixWindow : 
												    startbasenameWindow) : 
										(startbasenameWindow!=NULL ? 
													startbasenameWindow : 
												    startbasenameUnixWindow);
	startbasename = startbasename!=NULL? startbasename : n;
	const char* point=std::strchr(startbasename,'.');
	if(point)
		return std::string(startbasename+1,point-startbasename-1);  
	else
		return std::string(startbasename+1);  
		
}
bool fileExists(const std::string &pathAndFilename){
    std::FILE* in=std::fopen(pathAndFilename.c_str(),"rb");
    if(in){
        std::fclose(in);
        return true;
    }else
        return false;
}
void saveIntoFile(const char *filepath, const char *data){
    std::FILE *fp = std::fopen(filepath, "ab");
    if (fp != NULL)
    {
        fputs(data, fp);
        fclose(fp);
    }
}

void readFile(const char *path){
	//open file
	std::FILE * file = std::fopen(path, "rb");
	if(!file) EXITERROR("can't open file",-4)
	//get size file
	std::fseek(file, 0L, SEEK_END);
	size_buffer = ftell(file);
	std::fseek(file, 0L, SEEK_SET);
	if((size_buffer-START_LOCATION)>MEMORY_SIZE) EXITERROR("rom too big",-5)
	//read file
	std::fseek(file, 0L, SEEK_SET);
	std::fread(bfile,size_buffer,1,file);
	//close file
	std::fclose(file);
}
void printArray(std::string & in){
  char bitBuffer[255];
  const unsigned char *byte;
  long count=0;
  in+="{\n\t";
  for ( byte = bfile; size_buffer-(byte-bfile); ++byte ){
	 sprintf(bitBuffer, "0x%02X", *byte);
	 in+=bitBuffer;
	 if((byte-bfile)<size_buffer-1) in+=", ";
	 if((byte-bfile+1)%4==0) in+="\n\t";
   }
  in+="};\n";
}

int main( int argc,const char* args[] ){

	if(argc<2)  EXITERROR("few args",-1)
	//get file name
	std::string name(getFileName(args[1]));
	//set files names
	std::string nameH(name+".h");	
	if(fileExists(nameH.c_str())) EXITERROR("header olready exists",-2)
	std::string nameC(name+".c");
	if(fileExists(nameC.c_str())) EXITERROR("c file olready exists",-3)	
	//set memory
	std::memset(bfile,0,sizeof(bfile));
	//read file
	readFile(args[1]);
	//make files
	std::string nameUP(name);
	std::transform(nameUP.begin(), nameUP.end(),nameUP.begin(), ::toupper);
	//to string
	char size_buffer_string[]="0000";
	std::sprintf(size_buffer_string,"%d",size_buffer);
	//
	std::string hfile="#ifndef "+nameUP+"_H\n"
		              "#define "+nameUP+"_H\n\n\n"
		              "#include <avr/pgmspace.h>\n\n\n"
					  "#ifdef __cplusplus\n"
						"extern \"C\" {\n"
					  "#endif\n\n"
					  "#define "+name+"_SIZE "+size_buffer_string+"\n\n"
					  "extern PROGMEM  unsigned char "+name+"["+name+"_SIZE];\n\n"
					  "#ifdef __cplusplus\n"
						 "};\n"
					  "#endif\n"
					  "#endif";
	std::string cfile="#include \""+nameH+"\"\n\nPROGMEM  unsigned char "+name+"["+name+"_SIZE] =";
	printArray(cfile);
	//save into files
	saveIntoFile(nameH.c_str(),hfile.c_str());
	saveIntoFile(nameC.c_str(),cfile.c_str());
	//close 
	return 0;
}