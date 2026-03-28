# Trabalho Estrutura de Dados
Repositório destinado ao trabalho 1 de Estrutura de Dados - Room Reservation System

O programa consiste num sistema de alocação de disciplinas em sala de aula durante uma semana.

O usuário pode solicitar uma reserva de sala em um dia e horário específico e registrar novas disciplinas.

## Compilação

```
g++ main.cpp ReservationSystem.cpp ReservationRequest.cpp -o reservation_system
```

## Execução

```
./reservation_system
```

## Arquitetura do Programa

Um `ReservationSystem` possui o número de salas e a capacidade máxima de alunos correspondente. Cada sala possuí uma matriz 5x14, onde as as linhas são os dias da semana e as colunas são os horários. Cada entrada da matriz irá guardar o ID da disciplina, ID = 0 indica que a sala está disponível naquele horário.

O sistema guarda um array dinâmico de strings com os nomes das disciplinas, onde a posição da disciplina do array é o ID correspondente (o id da primeira disciplina adicionada é 1, a segunda é 2, etc.)

Uma requisição `ReservationRequest` necessita do nome do curso (deve estar na lista de cursos cadastrados), o dia, o horário de início e término e a quantidade de alunos matriculados.

A função `reserve` verifica se é possível reserva uma sala. É verificado em cada sala, se a quantidade de alunos é menor que a capacidade dela e se está disponível em todos os horários em que foi requirido, casa seja possível fazer uma reserva, a função atribui o ID corresponde (Se não encontrar o ID, é atribuido o valor 0)

A função `cancel` marca como id=0 em todas os horários das salas em que possuem o id da disciplina a ser cancelada.

A função `printSchedule` exibe a grade horária da semana por ordem de sala.
