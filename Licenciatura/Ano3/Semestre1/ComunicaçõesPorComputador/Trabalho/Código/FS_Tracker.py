import socket
import threading
import json
import uuid
import sys

class FS_Tracker:
    def __init__(self, address, port):
        self.address = address
        self.port = port
        self.uuid_generator = UniqueIdGenerator()
        # A key deste dicionário é o UUID e o valor é um dicionário com a chave sendo o número do bloco e o valor sendo o UUID, o Adress IP e a porta do nó que o possui
        self.nodes = {}
        # Lista com os UUIDs dos nós que estão conectados, a key é o UUID e os valores são o IP e a Porta
        self.nodesConnect = {}
        # Inicializa o socket TCP
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.address, self.port))
        self.server_socket.listen()
        self.lock = threading.Lock()
    
    
    def start(self):
        try:
            print(f"FS_Tracker listening on {self.address}:{self.port}")
            while True:
                client_socket, addr = self.server_socket.accept()
                print(f"New connection from {addr}")
                threading.Thread(target=(self.handle_client), args=(client_socket,addr)).start()
        except KeyboardInterrupt:
            # Close the socket when a KeyboardInterrupt is received (Ctrl+C)
            print("KeyboardInterrupt: Closing the socket...")
            self.stop()
    

    def stop(self):
        self.server_socket.close()
        
    def handle_client(self, client_socket,addr):
        print(f"Dentro do handle_client")
        try:
            while True:
                data = client_socket.recv(1024).decode('utf-8')
                if data == "":
                    print("Client socket interrupted")
                    c = {'Address': client_socket.getpeername()[0], 'Port': client_socket.getpeername()[1]}
                    value = {i for i in self.nodesConnect if self.nodesConnect[i]==c}
                    v = ''.join(value)
                    self.handle_disconnect(v)
                    break
                message = json.loads(data)
                message_type = message.get('type')
                print("Message type: " + message_type)
                if message_type == 'REG':
                    self.handle_register(message, client_socket)
                elif message_type == 'UPT':
                    self.handle_update(message, client_socket)
                elif message_type == 'LOC':
                    self.handle_locate(message, client_socket)
                elif message_type == 'DIS':
                    self.handle_disconnect(message['UUID'])
                    break
                else:
                    error_message = f"Unknown message type: {message_type}"
                    self.handle_error(message.get('UUID'), error_message)
        except Exception as e:
            print(f"Error processing message: {str(e)}")
        finally:
            client_socket.close()

    def handle_register(self, message, client_socket):
        try:
            node_uuid = self.uuid_generator.generate_unique_id()
            # Adicionar node ao nodesConnect
            with self.lock:
                self.nodesConnect[node_uuid] = {'Address': client_socket.getpeername()[0], 'Port': client_socket.getpeername()[1]}
                self.nodes[node_uuid]={}
            response = {'UUID': node_uuid, 'IP': client_socket.getpeername()[0]}
            client_socket.send(json.dumps(response).encode('utf-8'))
        except Exception as e:
            error_message = f"Error processing registration message: {str(e)}"
            self.handle_error(None, error_message)

    def handle_update(self, message, client_socket):
        try:
            #print(type(message.get('BlocksDic')))
            #print(self.nodes)
            node_uuid = message.get('UUID')
            blocks_dict = message.get('BlocksDic')
            #print(message.get('BlocksDic'))
            #print("antes do node uuid check na update")
            with self.lock:
                if node_uuid and node_uuid in self.nodesConnect.keys():
                    self.nodes[node_uuid] = {}
                    for filename, data in blocks_dict.items():
                        total_blocks = data['total_blocks']
                        existing_blocks = data['existing_blocks']
                        
                        if filename not in self.nodes[node_uuid]:
                            self.nodes[node_uuid][filename] = [None] * total_blocks
                            

                        for block_number in existing_blocks:
                            self.nodes[node_uuid][filename][block_number] = {'UUID': node_uuid, 'Address': client_socket.getpeername()[0], 'Port': client_socket.getpeername()[1]}
                            #print(self.nodes[node_uuid][filename])
                    #print(self.nodes[node_uuid][filename])
                    response = {'Status': 'Success'}
                    client_socket.send(json.dumps(response).encode('utf-8'))
                else:
                    error_message = "Update message does not contain the UUID."
                    self.handle_error(None, error_message)
                
                print(self.nodes)
        except Exception as e:
            error_message = f"Error processing update message: {str(e)}"
            self.handle_error(None, error_message)

    def handle_locate(self, message, client_socket):
        try:
            filename = message.get('FileName')
            block_number = message.get('BlockNumber')
            node_uuid = message.get("UUID")
            flag_file = False
            flag_block = False
            with self.lock:
                if filename:
                    for node_uuid1 in self.nodes.keys():
                        if filename in self.nodes[node_uuid1]:#####################################
                            flag_file = True
                            if block_number is not None:
                                # Procura por um bloco específico
                                block_number = int(block_number)
                                if self.nodes[node_uuid1][filename][block_number] is not None:
                                    flag_block = True
                                    location_info = self.nodes[node_uuid1][filename][block_number]
                                    response = {
                                            
                                        'BlocksTotal': 1,
                                        'BlockList': f"{block_number} - {location_info['Address']}:{location_info['Port']}"
                                    }
                                    client_socket.send(json.dumps(response).encode('utf-8'))
                            else:  # Procura por todos os blocos do arquivo
                                block_list = []
                                blocks_total = 0
                                blocks_total_local = 0
                                for node_uuid2 in self.nodes.keys():
                                    if filename in self.nodes[node_uuid2]:
                                        blocks_total_local = len(self.nodes[node_uuid2][filename])
                                        for i in range(blocks_total_local):
                                            if self.nodes[node_uuid2][filename][i] is not None:
                                                repCount = 0
                                                for b in block_list:
                                                    if i == int(b.split(" ")[0]):
                                                        repCount += 1
                                                if repCount < 1:
                                                    block_list.append(f"{i} - {self.nodes[node_uuid2][filename][i]['Address']}:{self.nodes[node_uuid2][filename][i]['Port']}")
                                                    blocks_total += 1


                                
                                response = {
                                    'BlocksTotal': blocks_total,
                                    'BlockList': ' ; '.join(block_list)
                                }
                                client_socket.send(json.dumps(response).encode('utf-8'))


                    if flag_file == False :  
                        error_message = f"File {filename} not found."
                        self.handle_error(node_uuid, error_message)
                        client_socket.send(json.dumps("FNF").encode('utf-8')) 

                    elif flag_block == False and block_number is not None:
                        error_message = f"Block {block_number} not found for file {filename}."
                        self.handle_error(node_uuid, error_message)
                        client_socket.send(json.dumps("BNF").encode('utf-8'))
                else:
                    error_message = f"No filename given."
                    self.handle_error(node_uuid, error_message)
                    client_socket.send(json.dumps("FNG").encode('utf-8'))
                
            

        except Exception as e:
            error_message = f"Error processing locate message: {str(e)}"
            self.handle_error(None, error_message)

    def handle_disconnect(self, node_uuid):
        try:
            # Remover node do nodesConnect
            with self.lock:
                del self.nodesConnect[node_uuid]
                del self.nodes[node_uuid]
                '''for x in self.nodes:
                    print(x)
                    for y in self.nodes[x]:
                        print(y)
                        for h in self.nodes[x][y]:
                            print(h)'''
        except Exception as e:
            error_message = f"Error processing disconnect message: {str(e)}"
            self.handle_error(None, error_message)
        
    def handle_error(self, node_uuid, error_message):
        if node_uuid in self.nodesConnect:
            node_info = self.nodesConnect[node_uuid]
            print(f"Error for Node {node_uuid} ({node_info['Address']}:{node_info['Port']}): {error_message}")
        else:
            print(f"Error for Node {node_uuid}: {error_message}")

        
class UniqueIdGenerator:
    def __init__(self):
        self.generated_ids = set()

    def generate_unique_id(self):
        unique_id = uuid.uuid4()
        while unique_id in self.generated_ids:
            unique_id = uuid.uuid4()
        self.generated_ids.add(unique_id)
        return str(unique_id)

if __name__ == "__main__":
    if len(sys.argv) < 1 or len(sys.argv) > 2:
        print("Comando não reconhecido. Formato expectavel: 'FS_Tracker.py' ou 'FS_Tracker.py <tracker_port>'")
        sys.exit(1)
    
    elif len(sys.argv) == 1:
        tracker_address = "10.4.4.1"
        tracker_port = 9090
        tracker = FS_Tracker(tracker_address, tracker_port)
        tracker.start()
    else:
        if sys.argv[1].isdigit():
                tracker_address = "10.4.4.1"
                tracker_port = int(sys.argv[1])
                tracker = FS_Tracker(tracker_address, tracker_port)
                tracker.start()
        else:
            print("Comando não reconhecido. Formato expectavel: 'FS_Tracker.py' ou 'FS_Tracker.py <tracker_port>'")