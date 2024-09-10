import os

# Mudar de Diretoria
os.chdir('../../EngWeb2024')

# Criar Pastas para 8 tpcs
for i in range(8):
    nomePasta = f"TPC{i+1}"
    os.mkdir(nomePasta)
    open(f"{nomePasta}/.gitkeep", 'w')

# Criar pasta "Projeto"
nomePasta = "Projeto"
os.mkdir(nomePasta)
open(f"{nomePasta}/.gitkeep", 'w')

# Criar pasta "Teste"
nomePasta = "Teste"
os.mkdir(nomePasta)
open(f"{nomePasta}/.gitkeep", 'w')

