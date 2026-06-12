# COMPUTAÇÃO DISTRIBUÍDA
## Trabalho - Banco de Dados Distribuído
https://github.com/luisTLD/distributed-db
- gRPC + Protocol Buffers (contrato .proto, stubs)
- Topologia full mesh (todo nó fala com todo nó)
- Relógio lógico de Lamport (tick / max+1)
- Exclusão mútua em 2 níveis (serialização no líder + lock por chave no 2PC)
- Eleição de líder (Bully) + adoção de estado mais recente (last_commit_ts)
- Two-Phase Commit (prepare / commit / abort)
- Protocolo de terminação (transação em dúvida, presumed abort)
- Quórum majoritário N/2+1 (anti split-brain)
- WAL + snapshot (durabilidade, recuperação pós-queda)
- Heartbeat + detector de falhas (timeout, suspeita imediata)
- Transferência de estado (SyncState no reingresso)
- Cliente com redirect (NOT_LEADER) e failover
- Testes: estresse concorrente, benchmark distribuído × local, verificação de consistência
---
## INTRODUÇÃO
### Sistema Distribuído
- Componentes em rede
- Comunicação por mensagens
- Sem relógio global
- Falhas independentes
### Desafios
- Heterogeneidade
- Abertura
- Segurança
- Escalabilidade
- Tratamento de falhas
- Concorrência
### Transparência
- Acesso
- Localização
- Replicação
- Falha
- Concorrência
- Migração
---
## COMUNICAÇÃO ENTRE PROCESSOS
### Sockets
- TCP (stream, confiável)
- UDP (datagrama, sem garantia)
### Marshalling
- Representação externa de dados
- Serialização / desserialização
- XDR, JSON, XML, Protocol Buffers
### Request-Reply
- Protocolo cliente-servidor
- Semânticas de falha
### Multicast
- Comunicação em grupo
- IP multicast
---
## INVOCAÇÃO REMOTA / JAVA RMI
### RPC
- Chamada remota como local
- Transparência de localização
### RMI
- Objetos remotos
- Stub (proxy) / Skeleton (despachante)
- RMI Registry
### Passagem de Parâmetros
- Por valor (objetos serializáveis)
- Por referência (objetos remotos)
### Semânticas de Invocação
- Talvez (maybe)
- Pelo-menos-uma (at-least-once)
- No-máximo-uma (at-most-once)
---
## SINCRONIZAÇÃO
### Relógios Físicos
- Skew e drift
- Cristian
- Berkeley
- NTP
### Relógios Lógicos
- Lamport (happened-before, max+1)
- Relógios vetoriais (causalidade exata)
### Estados Globais
- Corte consistente
- Snapshot de Chandy-Lamport
### Exclusão Mútua Distribuída
- Servidor central
- Anel com token
- Ricart-Agrawala (multicast + timestamps)
- Quórum (Maekawa)
- Critérios: segurança, vivacidade, ordem
---
## ELEIÇÃO DE LÍDER
### Objetivo
- Único coordenador
- Segurança + vivacidade
### Bully (valentão)
- Maior id vivo vence
- ELECTION / ANSWER / COORDINATOR
### Anel (Chang-Roberts)
- Ids circulando no anel
### Coordenação e Acordo
- Multicast confiável e ordenado (FIFO, causal, total)
- Consenso
- Falhas bizantinas
- Impossibilidade FLP (assíncrono)
---
## WEB SERVICES
### Conceito
- Serviço via HTTP
- Interoperabilidade
### SOAP
- Envelope XML
- WSDL (descrição)
- UDDI (descoberta)
### REST
- Recursos + URIs
- Verbos HTTP (GET/POST/PUT/DELETE)
- Stateless
- JSON
### Coreografia × Orquestração
---
## SERVIÇO DE NOMES 
### Nomes
- Nome × endereço × identificador
- Resolução de nomes
- Espaço de nomes hierárquico
### DNS
- Domínios, zonas, delegação
- Servidores autoritativos
- Cache e TTL
- Resolução iterativa × recursiva
### Diretório
- X.500 / LDAP
- Busca por atributos
---
## COMUNICAÇÃO INDIRETA
### Desacoplamento
- Espaço (não se conhecem)
- Tempo (não precisam coexistir)
### Comunicação em Grupo
- Membership
- Difusão para o grupo
### Publish-Subscribe
- Tópicos / conteúdo
- Brokers
### Filas de Mensagem (MOM)
- Ponto a ponto persistente
- Ex.: JMS, RabbitMQ, Kafka
### Espaço de Tuplas
- Linda: write / read / take
### Memória Compartilhada Distribuída (DSM)
---
## TRANSAÇÕES DISTRIBUÍDAS (Cap 17)
### ACID
- Atomicidade, Consistência, Isolamento, Durabilidade
### Estrutura
- Transações planas × aninhadas
- Coordenador + participantes
### Two-Phase Commit (2PC)
- Fase 1: votação (PREPARE, voto SIM/NÃO)
- Fase 2: decisão (COMMIT/ABORT)
- Bloqueante (coordenador cai → participante em dúvida)
- Terminação cooperativa / presumed abort
### Controle de Concorrência
- Locks + 2PL (two-phase locking)
- Ordenação por timestamp
- Otimista (validação)
### Deadlock Distribuído
- Wait-for graph
- Detecção por arestas (edge chasing)
### Recuperação
- Log (WAL)
- Pontos de verificação
---
## SISTEMAS PEER-TO-PEER
### Características
- Sem servidor central
- Nós simétricos
- Churn
### Gerações
- Napster (índice central)
- Gnutella (inundação)
- Estruturados (DHT)
### DHT
- Hash consistente
- Chord (anel + finger table)
- Pastry / Tapestry (roteamento por prefixo)
- Kademlia (XOR)
### Overlay
- Rede lógica sobre a física
---
## REPLICAÇÃO
### Objetivos
- Disponibilidade
- Tolerância a falhas
- Desempenho
### Modelos
- Replicação passiva (primário-backup)
- Replicação ativa (máquina de estados)
### Consistência
- Linearizabilidade
- Consistência sequencial
- Consistência eventual
### Quóruns
- Leitura R + escrita W > N
- Maioria (split-brain)
### Gossip
- Propagação epidêmica
- Alta disponibilidade, consistência relaxada
### View-Synchronous
- Grupos com visões
---
## SISTEMAS DE ARQUIVOS DISTRIBUÍDOS
### Requisitos
- Transparência (acesso, localização)
- Concorrência, replicação, cache
### NFS
- RPC, montagem remota
- Stateless (v3)
### AFS
- Cache de arquivos inteiros
- Callbacks (invalidação)
### Semânticas de Compartilhamento
- Unix (escrita visível na hora)
- Sessão (visível ao fechar)
---
## SISTEMAS DE IA DISTRIBUÍDOS
### Treinamento Distribuído
- Paralelismo de dados (mesmo modelo, dados particionados)
- Paralelismo de modelo (modelo particionado)
### Agregação
- Parameter server
- All-reduce (ring)
### Federated Learning
- Dados ficam no cliente
- Agregação de gradientes/pesos
### Inferência Distribuída
- Sharding de modelo
- Balanceamento de carga
---
## COMPUTAÇÃO UBÍQUA
### Conceito
- Computação invisível / em todo lugar
- Dispositivos móveis e sensores
### Características
- Sensibilidade a contexto
- Mobilidade (handoff)
- Descoberta espontânea de serviços
- Energia limitada
### Redes de Sensores
- Agregação de dados
- Comunicação ad hoc
### IoT
- Dispositivos conectados
- Edge / fog computing
