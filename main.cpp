#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib> // importa exit()

class tarefas{
	public:
		std::string titulo;

		tarefas(std::string titulo){
			this->titulo = titulo;
	}
};

void leTarefa();

void escreveTarefa();

void excluiTarefa();

void atualizaArquivo(const std::vector<tarefas>& tarefasLista);

int main(){

	int respostaMenu;

	while(1){
		std::cout<<std::endl<<"Choose an option: "<<std::endl<<"1. Write new task"<<std::endl<<"2. See all tasks stored"<<std::endl<<"3. Delete a task"<<std::endl<<"4. Quit"<<std::endl;
		std::cin>>respostaMenu;

		switch(respostaMenu){
			case 1:
				escreveTarefa();
				break;
			case 2:
				leTarefa();
				break;
			case 3:
				excluiTarefa();
				break;
			case 4:
				exit(0);
				break;
			default:
				std::cout<<"You selected an invalid input";
		}
	}

	return 0;
}

void leTarefa(){
	std::string tarefaTitulo;
	std::ifstream arquivo("tarefas.txt");

	if(arquivo.is_open()){
		unsigned int index = 1;
		while (std::getline(arquivo, tarefaTitulo)){
			std::cout << std::endl << index << ". " << tarefaTitulo << std::endl;
			index++;		
		}
	}else{
		std::cout<<"Unable to read tasks!"<<std::endl;
	}

	arquivo.close();
}

void escreveTarefa(){
	std::ofstream arquivo("tarefas.txt", std::ios::app); //abre arquivo no modo append

	if (arquivo.is_open()){
		std::string titulo;
		std::cout<<"Type the new task title: ";
		std::getline(std::cin >> std::ws, titulo);

		tarefas tarefa = tarefas(titulo);

		arquivo<<tarefa.titulo<<std::endl;

	}else{
		std::cerr<<"Unable to open tasks!"<<std::endl;
	}

	arquivo.close();
}

void excluiTarefa(){
	std::vector<tarefas> tarefasLista;
	std::ifstream arquivo("tarefas.txt");

	if(arquivo.is_open()){
		std::string tarefaTitulo;
		while(std::getline(arquivo, tarefaTitulo)){
			tarefasLista.push_back(tarefas(tarefaTitulo)); 
			// push_back() é basicamente um append()
		}
		arquivo.close();
	}else{
		std::cerr<<"Unable to read tasks!"<<std::endl;
		return;
	}

	if(tarefasLista.empty()){
		std::cout<<"There are no tasks to read!";
	}

	unsigned int index;

	leTarefa();
	std::cout<<std::endl<<"Enter the task number you want to delete: ";
	std::cin>>index;

	if(index > 0 && index < tarefasLista.size()){
		tarefasLista.erase(tarefasLista.begin() + (index - 1));
		atualizaArquivo(tarefasLista); // reescreve o arquivo aberto
		std::cout<<"Task deleted successfully";
	}else{
    	std::cout << "Invalid index!" << std::endl;
	}
}

void atualizaArquivo(const std::vector<tarefas>& tarefasLista){
	std::ofstream arquivo("tarefas.txt", std::ios::trunc);
	//abre arquivo no modo truncado (esvazia o arquivo)
	if(arquivo.is_open()){
		for (const auto& tarefa : tarefasLista){
			arquivo << tarefa.titulo << std::endl;
			/*como arquivo é do tipo ofstream, pode receber
			uma entrada usando o operador  <<, incluindo o newline*/
		}
	}else{
		std::cerr<<"Error opening the tasks!"<<std::endl;
		return;
	}
}