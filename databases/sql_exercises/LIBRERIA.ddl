-- *********************************************
-- * Standard SQL generation                   
-- *--------------------------------------------
-- * DB-MAIN version: 11.0.2              
-- * Generator date: Sep 14 2021              
-- * Generation date: Thu Mar 20 10:03:41 2025 
-- * LUN file: C:\Users\dedde\Desktop\_SCUOLA\Uni\databases\Libreria.lun 
-- * Schema: LIBRERIA/Logico1 
-- ********************************************* 


-- Database Section
-- ________________ 

create database LIBRERIA;


-- DBSpace Section
-- _______________


-- Tables Section
-- _____________ 

create table EDITORE (
     CodiceEditore char(1) not null,
     Ind_Via char(1) not null,
     Ind_Numero char(1) not null,
     Ind_Città char(1) not null,
     Nome char(1) not null,
     constraint IDEDITORE primary key (CodiceEditore));

create table LIBRO (
     Codice char(1) not null,
     Titolo char(1) not null,
     DataPubblicazione char(1) not null,
     Prezzo char(1) not null,
     NumeroCopieVendute char(1) not null,
     CodiceEditore char(1) not null,
     constraint IDLIBRO_ID primary key (Codice));

create table VENDITA (
     Codice char(1) not null,
     CodiceNegozio char(1) not null,
     Data char(1) not null,
     Quantità char(1) not null,
     constraint IDVENDITA primary key (Codice, CodiceNegozio, Data));

create table NEGOZIO (
     CodiceNegozio char(1) not null,
     Nome char(1) not null,
     Ind_Via char(1) not null,
     Ind_Numero char(1) not null,
     Ind_Città char(1) not null,
     constraint IDNEGOZIO primary key (CodiceNegozio));

create table AUTORE (
     CodiceAutore char(1) not null,
     Cognome char(1) not null,
     Nome char(1) not null,
     constraint IDAUTORE primary key (CodiceAutore));

create table Scrittura (
     Codice char(1) not null,
     CodiceAutore char(1) not null,
     constraint IDScrittura primary key (Codice, CodiceAutore));


-- Constraints Section
-- ___________________ 

alter table LIBRO add constraint IDLIBRO_CHK
     check(exists(select * from Scrittura
                  where Scrittura.Codice = Codice)); 

alter table LIBRO add constraint FKPubblicazione
     foreign key (CodiceEditore)
     references EDITORE;

alter table VENDITA add constraint FKRegistrazione
     foreign key (CodiceNegozio)
     references NEGOZIO;

alter table VENDITA add constraint FKRichiesta
     foreign key (Codice)
     references LIBRO;

alter table Scrittura add constraint FKScr_AUT
     foreign key (CodiceAutore)
     references AUTORE;

alter table Scrittura add constraint FKScr_LIB
     foreign key (Codice)
     references LIBRO;


-- Index Section
-- _____________ 

