#Antonio Ramos Gonzalez
#372576
#Clase Person
#30/05/2024
class Person:
    def __init__(self,name,age,gender):
        self.name=name
        self.age=age
        self.gender=gender
    def greet(self):
        print("Hola, mi nombre es: ",self.name)
        print(f"Tengo {self.age} anios")
        print("Y mi genero es ", self.gender)

    def farewell(self):
        print("Adios tonoto")


