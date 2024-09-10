import os
import socket
import json
import sys
import uuid
import threading
import time



block_size = 100

class FS_Node:
    def __init__(self, ffolder, tracker_address, tracker_port):
        self.own_ip = ""
        self.ffolder = ffolder
        self.tracker_address = tracker_address
        self.tracker_port = tracker_port
        # Universally unique identifier (UUID) do Node
        self.uuid = ""
        # Dicionário de arquivos e blocos que o Node possui. 
        # O nome dos arquivos deve ser "<nome>_<número do bloco>_<numero total de blocos>"
        # A key é o nome do file, o valor é um tuplo, uma lista de blocos e o numero total de blocos
        self.files = {}
        # Dicionário de informações de localização de blocos. A key é o nome do arquivo, o valor é um dicionário aonde a key é o bloco e o valor a sua localização
        self.block_locations = {}
        # Inicializa o socket TCP
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.register()
        self.update() #mudar forma como lê estrutura dos nomes dos ficheiros
        self.lock = threading.Lock()

        #UDP
        #self.socketUDPsend = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def connect_to_tracker(self):
        self.client_socket.connect((self.tracker_address, self.tracker_port))

    def send_message(self, message):
        self.client_socket.sendall(json.dumps(message).encode('utf-8'))

    def register(self):
        if not self.uuid:
            #Conecta-se ao tracker
            self.connect_to_tracker()
            #Envia msg de registo
            message = {'type': 'REG'}
            self.send_message(message)

            #recebe uuid
            response_data = self.client_socket.recv(1024).decode('utf-8')
            response = json.loads(response_data)

            if 'UUID' in response and 'IP' in response:
                self.uuid = response['UUID']
                self.own_ip = response['IP']
                print(f"Registo bem-sucedido! UUID atribuído: {self.uuid}")
                print(f"My ip: {self.own_ip}")
            else:
                print("Falha no registo. Tenta novamente.")
        else:
            print("Já estás registado.")

    def update(self):
        self.files = {}
        global block_size
        # Para cada arquivo na pasta
        for filename in os.listdir(self.ffolder):
            file_path = os.path.join(self.ffolder, filename)

            if os.path.isfile(file_path):
                total_size = os.path.getsize(file_path)
                total_blocks = (total_size + block_size - 1) // block_size

                if filename not in self.files:
                    self.files[filename] = {'total_blocks': total_blocks, 'existing_blocks': list()}

                with open(file_path, 'rb') as file:
                    for block_number in range(total_blocks):
                        # Calcula a posição do primeiro byte do bloco no arquivo
                        block_start = block_number * block_size
                        # Lê o primeiro byte do bloco
                        file.seek(block_start)
                        first_byte = file.read(1)

                        # Verifica se o primeiro byte é nulo (\x00)
                        if first_byte != b'\x00':
                            self.files[filename]['existing_blocks'].append(block_number)

        message = {'type': 'UPT', 'UUID': self.uuid, 'BlocksDic': self.files}
        self.send_message(message)

        response_data = self.client_socket.recv(1024).decode('utf-8')
        response = json.loads(response_data)

        if 'Status' in response and response['Status'] == 'Success':
            print("Atualização bem-sucedida.")
        else:
            print("Falha na atualização. Tenta novamente.")


    def locate(self, filename, block_number):
        if not self.uuid:
            print("Precisas de estar registado para poderes localizar ficheiros/blocos")
            return

        if not filename:
            print("Nome do ficheiro não fornecido.")
            return

        if block_number == 0:
            message = {'type': 'LOC', 'UUID': self.uuid, 'FileName': filename}
        else:
            message = {'type': 'LOC', 'UUID': self.uuid, 'FileName': filename, 'BlockNumber': block_number}

        self.send_message(message)

        # Aguarda a resposta do tracker
        response_data = self.client_socket.recv(1024).decode('utf-8')
        response = json.loads(response_data)

        if 'FNF' in response:
            print(f"File {filename} not found")
            return
        if 'BNF' in response:
            print(f"Block {block_number} from file {filename} not found")
            return

        if 'FNG' in response:
            print(f"Filename not given")
            return

        # Verifica se a resposta contém informações sobre o número total de blocos do arquivo
        if 'BlocksTotal' in response:
            print(f"Total de blocos: {response['BlocksTotal']}")

        # Verifica se a resposta contém a lista de blocos
        if 'BlockList' in response:
            print("Blocos:")
            # A lista de blocos é uma string no formato '1 - 192.168.1.2:9090 ; 2 - 192.168.1.1:9090 ;'
            block_list = response['BlockList']
            block_list = block_list.split(';')

            # Dicionário para armazenar as informações de localização
            block_locations2 = {}

            # Para cada bloco na lista
            for block_info in block_list:
                # Dividir as informações do bloco em número do bloco e endereço IP do Node
                block, node_address = map(str.strip, block_info.split('-'))

                # Dividir o endereço IP do Node em IP e porta
                node_ip, node_port = map(str.strip, node_address.split(':'))

                # Adicionar as informações ao dicionário
                block_locations2[block] = (
                    node_ip,
                    int(node_port)
                )

                # Imprimir as informações do bloco
                print(f"Bloco: {block}, Localizado em: {node_ip}:{node_port}")

            # Armazenar as informações no dicionário de localizações
            self.block_locations[filename] = block_locations2

                    
    def disconnect_from_tracker(self):
        if self.uuid:
            # Se o Node estiver registado, envia uma mensagem de desconexão para o tracker
            message = {'type': 'DIS', 'UUID': self.uuid}
            self.send_message(message)
        

        # Fecha o socket do cliente
        self.client_socket.close()
        print("Desconectado do tracker.")

    def getFile(self, file_name, bloco):
        if not self.uuid:
            print("Precisas de estar registado para poderes obter ficheiros/blocos.")
            return

        if not file_name:
            print("Nome do ficheiro não fornecido.")
            return
        
        if bloco < 0:
            print("Número do Bloco inválido.")
            return
        
        threads = []
        if bloco == 0:
            # Obter todos os blocos disponíveis para o arquivo
            if file_name in self.block_locations:
                available_blocks = self.block_locations[file_name].items()
                for block_number, address in available_blocks:
                    if address[0] != self.own_ip:
                        address = (address[0],6163)
                        #self.download_block(address, file_name, block_number, len(self.block_locations[file_name]))
                        t = threading.Thread(target=(self.download_block), args=(address, file_name, block_number, len(self.block_locations[file_name])))
                        t.start()
                        threads.append(t)
                    else:
                        print(f"You already have block {block_number}")
                del self.block_locations[file_name]
            else:
                print(f"Não há informações de localização para o arquivo {file_name}.")
        else:
            # Obter um bloco específico
            address = self.block_locations[file_name][str(bloco)]
            if address != '':
                if address[0] != self.own_ip:
                    address = (address[0],6163)
                    self.download_block(address, file_name, bloco, len(self.block_locations[file_name]))
                else:
                    print(f"You already have block {bloco}")
                
                if len(self.block_locations[file_name]) > 1:
                    del self.block_locations[file_name][str(bloco)]
                else:
                    del self.block_locations[file_name]
            else:
                print("Bloco não encontrado")
            
        # Esperar que todas as threads terminem
        for thread in threads:
            thread.join()
        
        self.update()
        

    def handle_loss(self,node_address,filename,block_number,socketS):
        message = {
            'type': 'REQ',
            'FileName': filename,
            'BlockNumber': block_number
        }
        response_data = False 
    
        socketS.settimeout(5)
        for x in range(5):
            socketS.sendto(json.dumps(message).encode('utf-8'), node_address)
            try:
                response_data = socketS.recv(1024)
                if response_data != "" and response_data is not None:
                    break
                else:
                    print(f"Try number {x} failed for downloading block {filename}:{block_number} (received empty string)")
            except socket.timeout:
                print(f"Try number {x} failed for downloading block {filename}:{block_number}")

        if(not response_data):
            print(f"Timeout exceeded too many times. Stopping download for block {filename}:{block_number}")
            return 
        
        response = json.loads(response_data.decode('utf-8'))
        return response

    def handle_loss2(self,node_address,filename,block_number,s):
        response = self.handle_loss(node_address,filename,block_number,s)

        if(not response):
            return False
        else:
            if 'Status' in response and response['Status'] == 'Success':
                return True
            else :
                return False


    def download_block(self, node_address, filename, block_number, leng):
        try:
            with self.lock:
                global block_size
                block_data = False
                with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
                    response = self.handle_loss(node_address,filename,block_number,s)
                    #print(f"Response: {response}")
                    if 'Status' in response and response['Status'] == 'Success':
                        s.settimeout(5)
                        for x in range(10):
                            try:
                                block_data = s.recv(1024)
                                #block_data = block_data.replace(b'\x00', b'')
                                print(f"++++++++++++++++{block_data}")
                                if block_data != "" and block_data is not None:
                                    if int(block_number) + 1 == leng:
                                        if b'\x00' in block_data:
                                            print(f"Try2 number {x} failed for downloading block {filename}:{block_number} (received empty string)")
                                            if not self.handle_loss2(node_address,filename,block_number,s) :
                                                return
                                        else:
                                            break
                                    else:
                                        if b'\x00' in block_data or len(block_data) < 100:
                                            print(f"Try2 number {x} failed for downloading block {filename}:{block_number} (received empty string)")
                                            if not self.handle_loss2(node_address,filename,block_number,s) :
                                                return
                                        else:
                                            break
                                else:
                                    print(f"Try2 number {x} failed for downloading block {filename}:{block_number} (received empty string)")
                                    if not self.handle_loss2(node_address,filename,block_number,s) :
                                        return
                            except socket.timeout:
                                print(f"Try2 number {x} failed for downloading block {filename}:{block_number}")
                                if not self.handle_loss2(node_address,filename,block_number,s) :
                                    return
                        
                        if(not block_data):
                            print(f"Timeout exceeded too many times. Stopping download for block {filename}:{block_number}")
                            return 
                        
                        
                        # Obtém o caminho local do arquivo
                        local_file_path = os.path.join(self.ffolder, filename)
                        block_number = int(block_number)
                        # Calcula a posição de escrita no arquivo com base no número do bloco e tamanho do bloco
                        write_position = (block_number) * block_size
                        # Se o arquivo não existir, cria o arquivo preenchido com espaços vazios
                        if not os.path.exists(local_file_path):
                            with open(local_file_path, 'wb') as local_file:
                                local_file.write(b'\x00' * write_position)
                        # Abre o arquivo local em modo de escrita binária ('rb+')
                        with open(local_file_path, 'rb+') as local_file:
                            # Ajusta a posição de escrita no arquivo
                            local_file.seek(write_position)
                            # Escreve os dados na posição calculada
                            local_file.write(block_data)

                        print(f"Block {block_number} downloaded successfully.")
                    else:
                        print(f"Failed to download Block {block_number} from {node_address}.")
        except Exception as e:
            print(f"Error during block download: {str(e)}")


    
    def upload_block(self, client_socket, filename, block_number, address):
        try:
            with self.lock:
                global block_size
                # Obtém o caminho local do arquivo
                local_file_path = os.path.join(self.ffolder, filename)
                block_number = int(block_number)
                # Calcula a posição de leitura no arquivo com base no número do bloco e tamanho do bloco
                read_position = (block_number) * block_size

                # Abre o arquivo local em modo de leitura binária ('rb')
                with open(local_file_path, 'rb') as local_file:
                    # Ajusta a posição de leitura no arquivo
                    local_file.seek(read_position)
                    # Lê os dados da posição calculada
                    block_data = local_file.read(block_size)

                    # Envia a mensagem de sucesso
                    response = {'Status': 'Success'}
                    client_socket.sendto(json.dumps(response).encode('utf-8'), address)
                    # Envia os dados do bloco para o cliente
                    client_socket.sendto(block_data, address)

                    print(f"Block {block_number} uploaded successfully.")
        except Exception as e:
            # Em caso de erro, envia uma mensagem de erro
            error_message = f"Error during block upload: {str(e)}"
            response = {'Status': 'Error', 'Message': error_message}
            client_socket.sendto(json.dumps(response).encode('utf-8'), address)



    def display_menu(self):
        
        client_thread = threading.Thread(target=self.handle_client, daemon=True)
        client_thread.start()
        
        while True:
            print("\n====== Menu Principal ======")
            if not self.uuid:
                print("1. Registrar FS_Node")
            else:
                print("2. Atualizar lista de arquivos")
                print("3. Localizar arquivo")
                print("4. Visualizar informações do Node")
                print("5. Visualizar informações de localização de blocos")
                print("6. Get file/block(s)")
            print("0. Sair")

            choice = input("Escolhe uma opção (0-6): ")

            if choice == '1':
                self.register()
            elif choice == '2' and self.uuid:
                self.update()
            elif choice == '3' and self.uuid:
                filename = input("Digita o nome do ficheiro: ")
                block_number = int(input("Digita o número do bloco (0 para todos): "))
                self.locate(filename, block_number)
            elif choice == '4' and self.uuid:
                self.view_node_info()
            elif choice == '5' and self.uuid:
                self.view_block_locations()
                #print(self.block_locations)
            elif choice == '6':
                file_name = input("Nome do ficheiro: ")
                bloco = input("Número do bloco (0 para todos): ")
                # Buscar o adress ao self.block_locations usando o file_name e o bloco
                #print(self.block_locations)
                if bloco.isdigit():
                    self.getFile(file_name, int(bloco))
                else:
                    print("Numero do bloco inválido.")
            elif choice == '0':
                self.disconnect_from_tracker()
                break
            else:
                print("Opção inválida. Tenta novamente.")

    def view_block_locations(self):
        if self.block_locations:
            print("\n====== Informações de Localização de Blocos ======")
            for filename, block_info in self.block_locations.items():
                print(f"Arquivo: {filename}")
                for block, location in block_info.items():
                    print(f"\tBloco: {block}, Localizado em: {location[0]}")
        else:
            print("Sem informações de localização disponíveis.")



    def handle_client(self):
       
       #criar um socket para receber mensagens
        udp_socket_listen = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        udp_socket_listen.bind((self.own_ip, 6163))
        print(f"Listening for UDP requests on {self.own_ip}:{6163}")
        try:
            while True:
                data, address = udp_socket_listen.recvfrom(1024)
                print(f"Request received from {address[0]}:{address[1]}")
                data = data.decode('utf-8')
                message = json.loads(data)
                message_type = message.get('type')
                print(f"Type of the received request: {message_type}")
                if message_type == 'REQ':
                    threading.Thread(target=(self.upload_block), args=(udp_socket_listen, message.get('FileName'), message.get('BlockNumber'), address)).start()
                    #self.upload_block(udp_socket_listen, message.get('FileName'), message.get('BlockNumber'), address)
                else:
                    error_message = f"Unknown message type: {message_type}"
                    self.handle_error(message.get('UUID'), error_message)

        except Exception as e:
            print(f"Error processing message: {str(e)}")
        finally:
            udp_socket_listen.close()

    def view_node_info(self):
        if self.uuid:
            print("\n====== Informações do Node ======")
            print(f"UUID do Nó: {self.uuid}")
            print(f"Endereço do Tracker: {self.tracker_address}")
            print(f"Porta do Tracker: {self.tracker_port}")
            print(f"Arquivos Registados:")
            for filename in self.files:
                print(f"\t{filename}: {self.files[filename]}")
        else:
            print("Não estás registado. Realiza o registro antes de visualizar as informações do Node.")

                
if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Uso: python FS_Node.py <pasta> <tracker_address> <tracker_port>")
        sys.exit(1)

    ffolder = sys.argv[1]
    tracker_address = sys.argv[2]
    if sys.argv[3].isdigit():
        tracker_port = int(sys.argv[3])
    else:
        print("<tracker_port> tem de ser um numero inteiro")
        print("Uso: python FS_Node.py <pasta> <tracker_address> <tracker_port>")

    fs_node = FS_Node(ffolder, tracker_address, tracker_port)
    fs_node.display_menu()
    