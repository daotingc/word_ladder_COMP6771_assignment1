with open('expected.txt') as f:
    lines = f.readlines()
    for line in lines:
        a = line.split()
        fn = lambda x : '"' + x + '"'
        a = [fn(x) for x in a]
        # print(a)
        print("{" + ', '.join(a) + "},")
