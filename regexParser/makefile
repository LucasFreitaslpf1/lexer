# Makefile para compilar projetos C++ com subpastas.
#
# Comandos:
#   make        -> Compila todo o código e gera o executável 'programa'.
#   make run    -> Compila (se necessário) e executa o programa.
#   make clean  -> Remove os arquivos objeto (.o) e o executável.
#

# --- Variáveis de Compilação ---

# Compilador C++ que será utilizado (g++ é o padrão)
CXX = g++

# Flags de compilação:
CXXFLAGS = -g

# Nome do arquivo executável que será gerado
EXEC = a.out

# --- Variáveis de Arquivos ---

# Encontra automaticamente todos os arquivos .cpp na pasta atual e na pasta 'arvore'
# A função 'wildcard' expande os padrões.
SRCS = $(wildcard *.cpp parser/*.cpp fragment/*.cpp state/*.cpp)

# Gera a lista de arquivos objeto (.o) correspondentes aos arquivos fonte (.cpp)
# Ex: main.cpp vira main.o, e arvore/arvore.cpp vira arvore/arvore.o
OBJS = $(SRCS:.cpp=.o)

# Comando para remover arquivos
RM = rm -f


# --- Regras (Targets) ---

# A primeira regra é a padrão, executada quando você digita apenas 'make'
# 'all' é um nome convencional para a regra principal de compilação.
.PHONY: all
all: $(EXEC)

# Regra para criar o arquivo executável final.
# Ela depende de todos os arquivos objeto (.o).
# O linker (g++) junta todos os .o para criar o executável.
$(EXEC): $(OBJS)
	@echo "Ligando os arquivos objeto para criar o executável: $(EXEC)"
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)
	@echo "Compilação concluída com sucesso!"

# Regra padrão para compilar um arquivo .cpp em um arquivo .o
# $< é o nome do primeiro pré-requisito (o arquivo .cpp)
# $@ é o nome do alvo (o arquivo .o)
# -c significa "compile, mas não linke"
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para compilar e executar o programa.
# Depende do executável 'programa'. Se o programa não estiver compilado ou
# se algum arquivo fonte foi alterado, o 'make' primeiro compilará tudo
# e depois executará este comando.
.PHONY: run
run: $(EXEC)
	@echo "Executando o programa..."
	./$(EXEC)

# Regra para limpar a pasta do projeto.
# Remove todos os arquivos .o (nas pastas) e o executável final.
.PHONY: clean
clean:
	@echo "Limpando arquivos gerados..."
	$(RM) $(OBJS) $(EXEC)
	@echo "Limpeza concluída."
