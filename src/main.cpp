#include <iostream>
#include "DirectoryListing.h"
#include "FileSystemTree.h"
void DFS(const std::string &path, CFileSystemTree::CEntry &entry);

int main(int argc, char *argv[]){
    // Your code here
    CFileSystemTree TheTree;
    if (argc >= 2){
	    for(int i = 0; i < argc; i++){
		    std::cout<<argv[i]<<std::endl;
	    }
    }
    bool finish = false;
    std::string input;
    std::string currentdir = "/";
    DFS(".", TheTree.Root());
    while(!finish){
	    std::cout<<"> ";
	    std::getline(std::cin, input);
	    if (input == "exit"){
		    finish = true;
            }
	    else if (input == "pwd"){
		    std::cout << currentdir << std::endl;
		    std::cout<<TheTree.Root().FullPath()<<std::endl;
	    }
	    else if (input.substr(0,6) == "mkdir "){
		    TheTree.Root().AddChild(input.substr(6));
	    }
	    else if (input.substr(0,3) == "cd "){
		    auto NodeIter = TheTree.Find(input.substr(3));
		    if (NodeIter == TheTree.NotFound()){
			    std::cout<<"No such directory called "<<input.substr(3)<<std::endl;
		    }

		    currentdir = input.substr(3);
	    }
	    else if (input.substr(0,3) == "rm "){
		    auto NodeIter = TheTree.Find(input.substr(3));
		    if (NodeIter == TheTree.NotFound()){
			    std::cout<<"No such directory called "<<input.substr(3)<<std::endl;
	            }
		    TheTree.Root().RemoveChild(input.substr(3));
	    }
	    else if (input == "tree"){
		    std::cout<<std::string(TheTree)<<std::endl;
	    }
	    else{
		    std::cout<<"No command "<<input<<", please try again."<<std::endl;
	    }
    }
    return EXIT_SUCCESS;
}

void DFS(const std::string &path, CFileSystemTree::CEntry &entry){
	std::vector< std::tuple< std::string, bool > > Entries;
	std::string PathWithSlash = path;
	if (PathWithSlash.back() != '/'){
		PathWithSlash += '/';
	}
	DirectoryListing::GetListing(path, Entries);
	for(auto &Entry : Entries){
		if(std::get<1>(Entry)){
			std::string DirName = std::get<0>(Entry);
			if((DirName != ".") and (DirName != "..")){
				entry.AddChild(DirName);
				DFS(PathWithSlash + DirName, *entry.Find(DirName));
			}
		}
		else{
		    entry.AddChild(std::get<0>(Entry));
		}
	}
}

