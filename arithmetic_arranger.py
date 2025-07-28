def arithmetic_arranger(problems, y=False):

    numbers = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]
    operandos = ["+", "-"]
    results = []
    num1_list = []
    num2_list = []
    line_list = []
    result_list = []

    if len(problems) > 5:
        return "Error: Too many problems."

    for x in problems:
        d = x.split()
        if len(d[0]) > 4 or len(d[2]) > 4:
            return "Error: Numbers cannot be more than four digits."
        elif d[1] not in operandos:
            return "Error: Operator must be '+' or '-'."
        elif any(x not in numbers for x in d[0]) or any(x not in numbers for x in d[2]): 
            return "Error: Numbers must only contain digits."
        elif d[1] == "+":
            calc = int(d[0]) + int(d[2])
            strCalc = str(calc)
            results.append((d[0], d[1], d[2], strCalc))
        elif d[1] == "-":
            calc = int(d[0]) - int(d[2])
            strCalc = str(calc)
            results.append((d[0], d[1], d[2], strCalc))

    for x in results:
        max_digits = max(len(x[0]), len(x[2]), len(x[3]))
        if len(x[0]) != 4:
            if len(x[3]) == 1:
                num1_str = x[0].rjust(max_digits + 2) 
                num2_str = f"{x[1]} {x[2].rjust(max_digits - 1)}"
                line = '-' * (max_digits + 2)
                result_str = x[3].rjust(max_digits + 2)

                num1_list.append(num1_str)
                num2_list.append(num2_str)
                line_list.append(line)
                result_list.append(result_str) 

            elif len(x[3]) == 2:
                num1_str = x[0].rjust(max_digits + 2) 
                num2_str = f"{x[1]} {x[2].rjust(max_digits)}"
                line = '-' * (max_digits + 2)
                result_str = x[3].rjust(max_digits + 2)

                num1_list.append(num1_str)
                num2_list.append(num2_str)
                line_list.append(line)
                result_list.append(result_str) 


            elif len(x[3]) == 3:
                num1_str = x[0].rjust(max_digits + 2) 
                num2_str = f"{x[1]} {x[2].rjust(max_digits)}"
                line = '-' * (max_digits + 2)
                result_str = x[3].rjust(max_digits + 2)

                num1_list.append(num1_str)
                num2_list.append(num2_str)
                line_list.append(line)
                result_list.append(result_str) 

            elif len(x[3]) == 4:
                num1_str = x[0].rjust(max_digits + 1) 
                num2_str = f"{x[1]} {x[2].rjust(max_digits - 1)}"
                line = '-' * (max_digits + 1)
                result_str = x[3].rjust(max_digits + 1)

                num1_list.append(num1_str)
                num2_list.append(num2_str)
                line_list.append(line)
                result_list.append(result_str) 

        
            else:
                num1_str = x[0].rjust(max_digits + 1) 
                num2_str = f"{x[1]} {x[2].rjust(max_digits - 1)}"
                line = '-' * (max_digits + 1)
                result_str = x[3].rjust(max_digits + 1)

                num1_list.append(num1_str)
                num2_list.append(num2_str)
                line_list.append(line)
                result_list.append(result_str)
        else:
            if len(x[3]) == 1:
                num1_str = x[0].rjust(max_digits + 2) 
                num2_str = f"{x[1]} {x[2].rjust(max_digits - 1)}"
                line = '-' * (max_digits + 2)
                result_str = x[3].rjust(max_digits + 2)

                num1_list.append(num1_str)
                num2_list.append(num2_str)
                line_list.append(line)
                result_list.append(result_str) 

            elif len(x[3]) == 2:
                num1_str = x[0].rjust(max_digits + 2) 
                num2_str = f"{x[1]} {x[2].rjust(max_digits)}"
                line = '-' * (max_digits + 2)
                result_str = x[3].rjust(max_digits + 2)

                num1_list.append(num1_str)
                num2_list.append(num2_str)
                line_list.append(line)
                result_list.append(result_str) 


            elif len(x[3]) == 3:
                num1_str = x[0].rjust(max_digits + 2) 
                num2_str = f"{x[1]} {x[2].rjust(max_digits)}"
                line = '-' * (max_digits + 2)
                result_str = x[3].rjust(max_digits + 2)

                num1_list.append(num1_str)
                num2_list.append(num2_str)
                line_list.append(line)
                result_list.append(result_str) 

            elif len(x[3]) == 4:
                num1_str = x[0].rjust(max_digits + 2) 
                num2_str = f"{x[1]} {x[2].rjust(max_digits)}"
                line = '-' * (max_digits + 2)
                result_str = x[3].rjust(max_digits + 2)

                num1_list.append(num1_str)
                num2_list.append(num2_str)
                line_list.append(line)
                result_list.append(result_str) 

        
            else:
                num1_str = x[0].rjust(max_digits + 1) 
                num2_str = f"{x[1]} {x[2].rjust(max_digits - 1)}"
                line = '-' * (max_digits + 1)
                result_str = x[3].rjust(max_digits + 1)

                num1_list.append(num1_str)
                num2_list.append(num2_str)
                line_list.append(line)
                result_list.append(result_str)            

    if y == False:
      arranged_problems = "    ".join(num1_list) + "\n" + "    ".join(num2_list) + "\n" + "    ".join(line_list)
      return arranged_problems
    else: 
      arranged_problems = "    ".join(num1_list) + "\n" + "    ".join(num2_list) + "\n" + "    ".join(line_list) + "\n" + "    ".join(result_list)
      return arranged_problems

print(arithmetic_arranger(['3801 - 2', '123 + 49']))

print(arithmetic_arranger(['3 + 855', '3801 - 2', '45 + 43', '123 + 49']))