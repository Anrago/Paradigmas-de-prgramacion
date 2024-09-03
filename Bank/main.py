#Antonio Ramos Gonzalez
#372576
#Archivo principal
#30/05/2024
from User import User
import os
import platform
system=platform.system()
def clear():
    if system == "Linux":
        os.system("clear")
    if system == "Windows":
        os.system("cls")
def pause():
    input("Oprima cualquier tecla para continuar")



def menuGeneral(opc):
    clear()
    if opc==1:
        print("registro banco ZAPOTECA")
        name=input("Nombre: ")
        age=input("Edad: ")
        password=input("Contrasenia: ")
        valPass=input("Validar contrasenia")
        gender=input("Genero: ")
        client=User()
        client.register(name,age,password,valPass,gender)
    elif opc==2:
        while(True):
            print("Login")
            noCard=input("Ingrese numero de tarjeta: ") 
            password=input("Ingrese contrasenia: ")
            client=User()
            val=client.Login(noCard,password)

            if(val):
                menuLogin(client)
                return
            else:
                print("Los datos no coinciden. Favor de intentarlo nuevamente")

        
def menuLogin(client):
    while(True):
        clear()
        print("1.-Depositar")
        print("2.-Retirar")
        print("3.-Transferir")
        print("4.-Mostrar informacion cuenta")
        print("5.-Cerrar Sesion")
        opc2=int(input("Elija una opcion: "))
        clear()
        if opc2 == 1:
            amount=float(input("Ingrese cantidad a depositar: "))
            client.account.DepositCash(amount)
        elif opc2 ==2:
            amount=float(input("Ingrese cantidad a retirar: "))
            client.account.WithdrawCash(amount)
        elif opc2 ==3:
            amount=float(input("Ingrese cantidad a transferir: "))
            InterBanKey=input("Ingrese clave interbancaria: ")
            client.account.Transaction(amount,InterBanKey)
        elif opc2 ==4:
            client.account.CheckBalance()
            pause()
        elif opc2 ==5:
            print("Hasta luego ",client.name)
            pause()
            return

clear()
print("1.-Registrarse")
print("2.-login")
opc=int(input("Elija una opcion: "))
menuGeneral(opc)




