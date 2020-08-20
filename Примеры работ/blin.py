#В этой программе мы ищем одинаковые участки хеша разных входных данных. Почему только участки? Потому что сравнивать полный хеш очень долго.
import hashlib#Библиотека хеш-функций. Есть некоторые, но не все. Установилась без проблем.
ass = dict()#Создаём словарь
for i in range(0,10000000):
    strin = hashlib.sha384(str(i).encode()).hexdigest()[0:12]#Генерируем хеш по семени i, берем от него 12 байт
    strin = strin[:0] + chr(ord(strin[0]) & 63) + strin[1:]#Обрезаем байт, так как проверку нужно начать со второго бита
    strin = strin[:11] + chr(ord(strin[11]) & 240) + strin[12:]#Аналогично, так как нам не нужен весь последний байт, обрезаем и его
    if strin in ass:#Если в словаре нашелся наш порезанный хеш, то
        print("Collision found for i =", ass[strin],"and for i = ", i)#Победа
        print ("Hash equals: ")
        print ( hashlib.sha384(str(ass[strin]).encode()).hexdigest())#Выводим что за хеш в словаре
        print("and")
        print(hashlib.sha384(str(i).encode()).hexdigest())#И что мы нашли уже после добавления в словарь
        break
    else:#Ну, иначе мы этот резаный хеш записываем в словарь
        ass[strin] = i

