/* cinema_porb
 * Author: daniel
 * Creation date: 14/05/2025
 */
MACHINE
    Cinema_ProB
EXTENDS Cinema
    
CONSTANTS
    /*SALA*/
    VIP, NORMAL1,NORMAL2,NORMAL3, DBOX
    
    /*FILME*/
    ,As_Trancas_do_Rei_Careca, Poeira_em_Alto_Mar, Freira_e_o_Cavalo, Banheira_do_Gugu
    ,Volta_dos_que_Nao_Foram,Seu_Cuca_e_Eu, Meu_Tio_e_Filho_Unico, Didi_Quer_ser_Crianca,
    Eles_Vivem_Brigando, So_Sabem_Falar_Dela


PROPERTIES
    VIP: SALA & DBOX: SALA & NORMAL1: SALA &NORMAL2: SALA & NORMAL3: SALA 
    & SALA={VIP,NORMAL1,NORMAL2,NORMAL3, DBOX} 
    & card(SALA) = 5
    
    
    & As_Trancas_do_Rei_Careca:FILME 
    & Poeira_em_Alto_Mar:FILME 
    & Freira_e_o_Cavalo:FILME 
    & Banheira_do_Gugu:FILME 
    & Volta_dos_que_Nao_Foram:FILME 
    & Seu_Cuca_e_Eu:FILME 
    & Meu_Tio_e_Filho_Unico:FILME 
    & Didi_Quer_ser_Crianca:FILME 
    & Eles_Vivem_Brigando:FILME 
    & So_Sabem_Falar_Dela:FILME 
    
    & FILME={
        As_Trancas_do_Rei_Careca, Poeira_em_Alto_Mar, Freira_e_o_Cavalo,
        Banheira_do_Gugu
        ,Volta_dos_que_Nao_Foram,Seu_Cuca_e_Eu, 
        Meu_Tio_e_Filho_Unico, Didi_Quer_ser_Crianca,
        Eles_Vivem_Brigando, So_Sabem_Falar_Dela
    }
    & card(FILME) = 10
    
//    &maxCapacidade = 10
//    &limit_salas = 7
//    &limit_filmes = 20

END
