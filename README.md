
1. Introdução

Simulador de corridas de carros em C++. O simulador engloba alguns conceitos óbvios 
tais como Corrida, Carro, Piloto, Autódromo, Pista e Garagem (pode haver mais). Cada um destes 
conceitos é explicado abaixo. No entanto é muito importante que considere o seguinte:
 - Apenas as principais entidades são descritas. Outras entidades, com maior ou menor 
relevância, poderão ser necessárias.
 - Não existe necessariamente a relação uma entidade – uma classe. É muito provável que essa 
relação exista, mas pode acontecer que a representação de uma entidade/conceito seja 
distribuída por várias classes, ou apenas como atributo de outra.
 - A descrição foca principalmente as propriedades e comportamentos de cada conceito/classe. 
Os detalhes específicos sobre métodos e dados, incluindo os que não são mencionados 
explicitamente, devem ser deduzidos e implementados.
 - Os membros das classes devem ser deduzidos em função do comportamento desejado para 
cada classe, consoante o conceito que essa classe representa. Deve escolher tipos e estruturas 
de dados que façam sentido. Deve ter particular atenção em evitar estratégias que fariam 
sentido em C mas não em C++.
 - Há mais do que uma estratégia e implementação possíveis.

2. Carros

Um carro é um pequeno dispositivo que simula um veículo real com o seguinte comportamento:
 - Possui marca e modelo. Nenhum carro pode ser criado sem marca. O modelo também deve 
ser definido no início, mas se nada for dito, terá o modelo "modelo base".
 - Cada carro tem uma identificação (uma letra de a a z) que é automaticamente atribuída na 
criação do carro. Se houver mais carros que letras, os excedentes ficam com a letra ‘?’. A 
atribuição da letra é automática (sem intervenção do resto do programa), sento o primeiro o 
‘a’.
 - É elétrico e possui uma certa quantidade de energia (em mAh). Pode ser carregado, mas para 
isso deve estar parado. O processo de carregamento envolve uma manivela que fornece n
mAh, sendo n maior que zero. O carro não permitirá ultrapassar a capacidade máxima da sua 
bateria. A capacidade máxima e a capacidade inicial são características especificadas quando 
um carro é fabricado. O valor n é indicado quando a operação é feita.
 - Pode estar em movimento ou parado. Quando em movimento, avança a uma determinada 
velocidade (metros por segundo). 
 - Em movimento, um carro pode manter a sua velocidade, acelerar ou travar. O acelerador 
pressupõe dois usos: pressionar (o pedal do) acelerador e largar (o pedal do) acelerador. 
Enquanto o acelerador estiver pressionado, é exercido o seu efeito, que é de aumentar a 
velocidade do carro em 1m/s. O efeito é exercido apenas uma vez por segundo e mantém-se 
até o (pedal do) acelerador ser largado. Quer isto dizer que se quiser aumentar em 2m/s o 
acelerador terá que ser premido, mantido premido durante 2 segundos e depois largado, ou 
então premido e largado duas vezes. Pode-se premir e largar imediatamente, sendo exercido 
o seu efeito; no entanto, só se pode premir uma vez em cada segundo, e só se pode largar 
uma vez em cada segundo.
 - O carro possui também um travão que tem um funcionamento exatamente nos mesmos 
moldes que o acelerador, sendo a única diferença a de diminuir a velocidade em 1m/s em vez 
de a aumentar. Tudo o resto é igual ao acelerador.
 - Existe uma velocidade máxima, que é um dos parâmetros da construção de um carro. Essa 
velocidade máxima nunca será ultrapassada. De igual forma, a velocidade nunca será inferior 
a 0. Não é possível pressionar simultaneamente os pedais para acelerar e travar.
3
 - Mover consome energia: 0,1 mAh por segundo por metro/s. Se não houver energia, o carro 
diminui a velocidade, como se estivesse a travar (continuamente, perdendo 1m/s por cada 
segundo). Se além disso o condutor travar, o seu efeito é somado ao efeito de perda de 
velocidade por falta de energia.
 - Possui um sinal de emergência que pode ser ligado ou desligado, independentemente da 
velocidade.
 - Um carro faz tudo o que foi descrito acima apenas se tiver um piloto (veja abaixo) – é o piloto 
que opera os vários mecanismos no carro em que está. Só pode estar um piloto dentro do 
carro. O piloto pode sair ou entrar no carro apenas quando este estiver parado. 
 - O carro deve ter uma maneira de saber que passou (mais) um segundo (tempo). Isso permitirá 
que ele simule o seu comportamento (por exemplo, gastar energia enquanto se move, 
acelerar, travar, etc.).
 - Um carro pode ficar irremediavelmente danificado. Se isso acontecer, o carro fica 
imediatamente com velocidade 0 e deixará de responder a qualquer comando exceto os dois 
seguintes: tirar de um autódromo, continuando a existir (ver adiante) e remover de todo 
(deixar de existir). Se o carro tiver um dano irreparável, o piloto perde a vida (obviamente, se 
lá estiver um piloto no momento).
 - Um carro danificado não aceita condutor.

3. Pilotos

O piloto é um pequeno robô que simula o comportamento de um piloto real. Possui as seguintes 
características:
 - Tem um nome, atribuído quando é fabricado (tal como as pessoas reais, quando nascem) e 
nunca muda.
 - O nome de cada piloto é único. Este aspeto é verificado automaticamente pela classe que, se 
detetar repetição, modificará o nome dado automaticamente de forma a ser único.
 - Pode estar a conduzir um carro, ou seja, estar dentro desse carro. Naturalmente, num dado 
instante só pode conduzir um carro. Pode operar os mecanismos do carro que está a conduzir. 
Isto implica que o piloto tenha a capacidade de decidir o que vai fazer com o carro, e também 
a capacidade de receber ordens (vindas do exterior) para fazer determinada ação. Por 
exemplo: o piloto pode decidir travar, mas também pode receber uma ordem para o fazer 
(imagine um agente da autoridade que o manda parar por excesso de velocidade – quer ver 
os documentos). Basicamente, tudo o que pode ser feito com o carro pode ser decidido pelo 
condutor ou por via de uma ordem vinda “de fora”.
 - Pode receber ordens para entrar num carro específico ou sair do carro em que se encontra. 
 - Pode estar a competir numa corrida. Ao conduzir, a cada segundo da corrida, o piloto exibe 
um determinado comportamento de acordo com sua personalidade que o poderá levar a fazer 
algo, tal como, operar os controlos do carro de uma certa maneira. A personalidade específica 
de um piloto depende do seu tipo, conforme descrito abaixo.

4. Crazy Driver

Este tipo de piloto exibe o seguinte comportamento ao competir:
 - É desatento e só se lembra de começar a correr no Xº segundo da corrida (sendo X um número 
aleatório entre 1 e 5).
 - A cada novo segundo, pergunta à pista qual é o seu lugar na corrida (ver abaixo). Se não estiver 
no primeiro ou no último lugar, acelera. Se estiver em primeiro, mantém a velocidade. Se 
estiver em último, fica de mau humor e trava.
 - Se notar que perdeu lugares (“ficou mais para trás”) desde o instante (segundo) anterior, pisa 
no acelerador de forma a aumentar a velocidade em 2 m/s (exceto se estiver no último lugar, 
conforme descrito acima). Se o carro ficar sem energia, entra em pânico e acende o sinal de 
emergência.
 - Existe uma probabilidade de 5% deste condutor fazer algo que danifica irremediavelmente o 
automóvel. Quando isso acontece, o automóvel no lugar imediatamente atrás também fica 
irremediavelmente danificado (o condutor assusta-se e despista-se) e mais nenhum 
automóvel sofre com isso.

5. Piloto Rápido

O piloto rápido exibe o seguinte comportamento:
 - É extremamente ansioso e começa a correr no primeiro segundo da corrida. 
 - Acelera continuamente até ver que a energia restante do carro atingiu metade da sua 
capacidade máxima. Por precaução, a partir desse momento, ele só atuará o acelerador uma 
vez (para + 1m/s) a cada 3 segundos.
 - Devido à sua ansiedade, a cada 10 segundos tem uma probabilidade 10% de sofrer um ataque 
de pânico, e, caso se verifique esta situação, ativa o botão de emergência.

6. Piloto Surpresa

Defina e implemente outro tipo de piloto que se comporte de maneira diferente dos dois anteriores. 
Esse tipo de piloto deve ser implementado apenas pelo seu grupo (por outras palavras, não é nada 
boa ideia aparecerem pilotos surpresa iguais em grupos diferentes).

7. DVG

É a entidade que tem o registo de todos os carros e pilotos e a responsável direta pela existência 
destes objetos. Será esta a entidade alvo de backup caso o utilizador assim o determine (ver na seção 
de comandos).

8. Autódromo: Pista e Garagem 

O Autódromo compreende a pista propriamente dita, onde os carros competem, e uma garagem, 
onde os carros estão temporariamente armazenados quando não estão a competir. Pista e garagem 
são conceitos autocontidos, mas não existem fora do contexto do autódromo em que estão inseridos. 
O autódromo tem um nome que lhe permite distinguir-se de outros autódromos. O nome de cada 
autódromo é único, sendo isto validado e corrigido automaticamente pela classe em questão. O 
Autódromo tem uma pista certificada para um máximo de N carros. O número N é um dos parâmetros 
da sua construção. A pista tem um determinado comprimento em metros, correspondendo à distância 
entre a linha de partida e a linha de chegada. Esta distância é uma característica inicial do autódromo 
e nunca poderá ser alterada, pois o autódromo já está construído e não é feito de borracha.
Os carros não pertencem ao autódromo e podem sair de um autódromo e irem para outro, para 
competirem noutras corridas. No entanto, se um autódromo for destruído (por exemplo, ocorreu uma 
inundação), todos os carros que estejam nele ficam irremediavelmente danificados e consideram-se 
automaticamente fora desse autódromo. Presume-se que é possível um carro não estar em nenhum 
autódromo a um dado instante. Estará então apenas sob a alçada da direção geral de viação, que é 
quem realmente controla a existência dos carros. Esta entidade também controla a existência dos 
pilotos.
A corrida decorre na pista, onde os carros são colocados para esse efeito. Quando uma corrida está a 
decorrer, a pista mantém o controle da posição e lugar de cada um dos carros que estão a competir. 
O carro estará numa determinada posição a partir do início da pista (o sítio onde está nesse 
momento), e estará num determinado lugar (na corrida), sendo o primeiro lugar o que vai mais à 
frente. Os veículos que se encontram na garagem não são contados para o máximo de N carros e não 
competem em corridas. A pista exibe o seguinte comportamento:
 - A pista permite a adição de carros, desde que a corrida ainda não tenha começado. Os carros 
são colocados lado a lado. A pista é como a das corridas dos 100 metros olímpicos: existem N 
linhas, uma para cada carro.
 - A pista permite a inserção de um piloto num carro. Obviamente, só terá efeito se o carro 
estiver vazio e parado, conforme as regras do carro.
 - A pista permite que se comece a corrida. Isso só acontece se houver pelo menos dois carros 
concorrentes na pista e todos os veículos na pista tiverem condutor. Após o início da corrida, 
mais nenhum carro é aceite e nenhuma mudança de piloto é permitida.
 - A pista permite fazer avançar o tempo em um ou mais segundos na corrida, se esta já tiver 
começado e não terminado. Cada vez que esse mecanismo é ativado, a pista indica a cada um 
dos carros que o tempo avançou. Note que no caso de se avançar mais do que um segundo 
de uma vez, os carros terão que ser informados explicitamente de cada um desses segundos 
para que o seu comportamento seja correto (exemplo, a aceleração e travagem).
 - Se algum carro ligar o sinal de emergência, será removido da corrida e movido para a garagem. 
A garagem é um local que permite armazenar carros. Quando um carro é colocado na 
garagem, é indicado ao piloto para deixar o veículo, porque, para ele, a corrida acabou.
 - Permite terminar a corrida. Os carros são removidos da pista e vão para a garagem, e os pilotos 
saem dos veículos.
 - Possui um mecanismo para obter (“obter” ≠ “mostrar” ) a informação relacionada com uma 
corrida, indicando se ela já foi iniciada ou não, e, em caso afirmativo, detalhando a 
classificação atual.

9. Campeonato

Existe ainda o conceito de campeonato:
 - Um campeonato é composto por um conjunto de corridas, cada uma a decorrer num 
autódromo diferente, uma de cada vez. Portanto, Campeonato é um conceito por si só que 
agrega um conjunto de Autódromos nos quais decorre uma corrida em cada um deles por 
uma certa ordem. 
 - A associação pilotos/carros e os autódromos participantes são definidos antes do início do 
campeonato e não podem ser modificados a meio.
 - Carros que fiquem irremediavelmente danificados numa corrida falham o resto do 
campeonato.
 - No final de cada corrida é atribuída pontuação aos pilotos: 10 pontos para o primeiro 
classificado, 5 pontos para o segundo e 2 pontos para o terceiro. Estas pontuações só são 
atribuídas caso os pilotos tenham terminado a corrida.
 - O campeonato deve manter uma classificação dos pilotos, permitindo mostrar o campeão e o 
vice-campeão quando as corridas terminarem.
 - Existem vários aspetos e funcionalidades que devem ser analisados e definidos pelos alunos:
    - É necessário definir um conjunto de carros, pilotos e autódromos para um
campeonato. Esta é a "população" para as várias corridas. 
    - Devem existir mecanismos para efetuar a próxima corrida, ver pontuações, etc. (e 
outras funcionalidades óbvias).
    - Deve ser possível ao campeonato propagar comandos para os pistas, carros e pilotos.
Toda esta funcionalidade será acionada através de comandos do utilizador, descritos mais adiante.
