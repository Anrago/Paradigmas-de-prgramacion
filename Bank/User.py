#Antonio Ramos Gonzalez
#372576
#Clase User
#30/05/2024
from  BankClass import BankClass
from Person import Person
from random import randint

class User(Person):
    def __init__(self):
        super().__init__('','','')
        self.__password=''
        self.__noClient=0
        self.account=BankClass()

    def register(self,name,age,password,valPass,gender): 
        self.name=name
        self.age=age
        if int(self.age)<18:
            print("Lo sentimos, para crear una cuenta se debe de contar con una edad minima de 18 años:")
            return
        self.gender=gender
        self.__password=password
        while(True):
            if self.__password!=valPass:
                print("Las contraseñas no coincide. Favor de intentarlo nuevamente")
            else:
                break
        print("La cuenta ha sido creada con exito")
        print("Bienvenido al la familia de BANCO ZAPOTECA.")
        self.account._noCard=randint(1000000000000000,9999999999999999)
        self.account._interBanKey='542965'+str(randint(10000000000,99999999999))+str(randint(0,5))
        self.__noClient=randint(10000,99999)
        print("Su numero de cliente es: ",self.__noClient)
        print("Su No. de tarjeta es: ",self.account._noCard) 
        print("Su clave interbacaria es: ",self.account._interBanKey)
        print("Su saldo inicial sera de : ",self.account._balance," $")
        fa=open("Bank/Cuentas.txt","a")
        
        fa.write(str(self.__noClient) + ' ' + self.name + ' ' + self.__password + ' '
                 + str(self.account._noCard) + ' ' + str(self.account._interBanKey) + ' ' + str(self.account._balance) + '\n')
        fa.close()

    def Login(self,noCard, password):
        fa=open("Bank/Cuentas.txt","r")
        for line in fa:
            part=line.split()
            if part[2] == password and part[3]==noCard:
                print("Login Realizado con exito")
                self.account._balance=part[5]
                self.account._interBanKey=part[4]
                self.account._noCard=part[3]
                self.name=part[1]
                fa.close()
                return True
        fa.close()
        return False
    

  

        
        


    








