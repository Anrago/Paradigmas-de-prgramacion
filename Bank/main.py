from User import User

def menu(opc):
    if opc==1:
        print("registro banco LOS NACOS")
        name=input("Nombre: ")
        age=input("Edad: ")
        password=input("Contrasenia: ")
        valPass=input("Validar contrasenia")
        gender=input("Genero: ")
        client=User()
        client.register(name,age,password,valPass,gender)
    elif opc==2:
        print("Login")
        noCard=input("Ingrese numero de tarjeta: ")
        password=input("Ingrese contrasenia: ")
        client=User()
        client.Login(noCard,password)
        client.account.CheckBalance()

print("1.-Registrarse")
print("2.-login")
opc=int(input("Elija una opcion: "))
menu(opc)
