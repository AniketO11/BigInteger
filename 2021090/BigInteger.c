#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"BigInteger.h"
// Function to truncate leading zeros in a BigInteger
SBI truncate(SBI I) {
    SBI result = I;
    LL* current = result.data;
    while (current && current->data == 0) {
        LL* temp = current;
        current = current->next;
        free(temp);
        result.length--;
    }
    result.data = current;
    return result;
}



LL* newNodeAtEnd(LL* ll, int data) {
    LL* itr = ll, *temp = (LL*)malloc(sizeof(LL));
    if (!temp) {
        printf("Error encountered while storing data. [Notice: Heap memory might be full.]\n");
    } else {
        temp->data = data;
        temp->next = NULL;
        if (!ll) {
            ll = temp;
        } else {
            while (itr->next) {
                itr = itr->next;
            }
            itr->next = temp;
        }
    }
    return ll;
}

void printReverse(LL* itr) {
    if (!itr) {
        return;
    }
    printReverse(itr->next);
    printf("%d", itr->data);
}

SBI initialize(char* S) {
    SBI var;
    var.length = 0;
    var.sign = 1;  // Default sign is positive
    char digit;
    int len = strlen(S);

    if (len > 0 && S[0] == '-') {
        var.sign = -1;  // If the string starts with '-', it's a negative number
        S++;  //To move the pointer past the '-' character
        len--;     // Decrease the length accordingly
    }
    while(len>0&&S[0]==0)
    {
        S++;
        len--;
    }
    LL* head = NULL;
    LL* tail = NULL; // Keep track of the tail of the linked list

    for (int i = len-1; i>=0; i--) {
        digit = S[i];
          if (digit=='\0')
             break;
        if ( digit >= '0' && digit <= '9') {
            int value = digit - '0';
            LL* newNode = (LL*)malloc(sizeof(LL));
            if (!newNode) {
                printf("Error: Memory allocation failure.\n");
                // Handle memory allocation failure.
                return var;
            }
            newNode->data = value;
            newNode->next = NULL;
            if (!head) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            var.length++;
        } else {
            printf("Error: Invalid character in input.\n");
            // Handle invalid input character (e.g., non-numeric character)
            // You can choose to return an error state or handle it differently.
            return var;
        }
    }

    var.data = head;
    return var;
}




// Custom function to compare two BigIntegers
int compareBigInt(SBI I1, SBI I2) {
    if (I1.length > I2.length)
        return 1;
    if (I1.length < I2.length)
        return -1;

    LL* ptr1 = I1.data;
    LL* ptr2 = I2.data;
    while (ptr1 && ptr2) {
        if (ptr1->data > ptr2->data)
            return 1;
        if (ptr1->data < ptr2->data)
            return -1;
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    return 0;
}

// Custom function to add one to a BigInteger
SBI addOne(SBI I) {
    SBI result;
    result.sign = I.sign;
    result.length = I.length;
    result.data = NULL;

    LL* ptr = I.data;
    int carry = 1;

    while (ptr) {
        int sum = ptr->data + carry;
        result.data = newNodeAtEnd(result.data, sum % 10);
        carry = sum / 10;
        ptr = ptr->next;
    }

    if (carry)
        result.data = newNodeAtEnd(result.data, carry);

    result.length++;

    return result;
}

// Custom function to multiply a BigInteger by a single digit
SBI mulOne(SBI I, int digit) {
    SBI result;
    result.sign = I.sign;
    result.length = I.length;
    result.data = NULL;

    LL* ptr = I.data;
    int carry = 0;

    while (ptr) {
        int product = ptr->data * digit + carry;
        result.data = newNodeAtEnd(result.data, product % 10);
        carry = product / 10;
        ptr = ptr->next;
    }

    if (carry)
        result.data = newNodeAtEnd(result.data, carry);

    result.length++;

    return result;
}

// Custom function to convert an integer to a BigInteger
SBI intToBig(int num) {
    SBI result;
    result.sign = 1;
    result.length = 0;
    result.data = NULL;

    if (num == 0)
        return result;

    while (num > 0) {
        result.data = newNodeAtEnd(result.data, num % 10);
        result.length++;
        num /= 10;
    }

    return result;
}

// Custom function to multiply a BigInteger by 10
SBI mulByTen(SBI I) {
    SBI result;
    result.sign = I.sign;
    result.length = I.length + 1;
    result.data = newNodeAtEnd(I.data, 0); // Add a 0 to the end to multiply by 10

    return result;
}

LL* newNode(int data) //Creates a new LL node and return its address. 
{
    LL *temp = (LL*)malloc(sizeof(LL));
    if (!temp) {
        printf("Error encountered while storing data. [Notice: Heap memory might be full.]\n");
    } else {
        temp->data = data;
        temp->next = NULL;
    }
    return temp;  
}

// Function to display a BigInteger with its sign
void display(SBI I) {
    LL* temp = I.data;
    if (!I.data) {
        printf("Error: Input is not initialized with any big integer.\n");
    } else {
        if (I.sign == -1) {
            printf("-");
        }
        truncate(I);
        printReverse(temp);
        printf("\n");
    }
}

// Function to add two BigIntegers with appropriate signs
SBI add(SBI I1, SBI I2) {
    SBI var;
    var.sign = 1;
    var.length = 0;
    var.data = NULL;
    int carry = 0;

    if (I1.sign == -1 && I2.sign == -1) {
        var.sign = -1;
    } else if (I1.sign != I2.sign) {
        if (I1.sign == -1) {
            I1.sign = 1;
            var = sub(I2, I1);
        } else {
            I2.sign = 1;
            var = sub(I1, I2);
        }
        return var;
    }

    LL* i1 = I1.data;
    LL* i2 = I2.data;

    while (i1 || i2 || carry) {
        int x = (i1 ? i1->data : 0);
        int y = (i2 ? i2->data : 0);
        int sum = x + y + carry;
        carry = sum / 10;
        var.data = newNodeAtEnd(var.data, sum % 10);
        var.length++;
        if (i1) i1 = i1->next;
        if (i2) i2 = i2->next;
    }

    return truncate(var);
}

// Function to subtract two BigIntegers with appropriate signs
SBI sub(SBI I1, SBI I2) {
    SBI var;
    var.length = 0;
    var.data = NULL;

    if (!I1.data)
        printf("Error: I1 has not been initialized.\n");
    else if (!I2.data)
        printf("Error: I2 has not been initialized.\n");
    else {
        if (I1.sign == -1 && I2.sign == 1) {
            I2.sign = -1;
            var = add(I1, I2);
        } else if (I1.sign == 1 && I2.sign == -1) {
            I2.sign = 1;
            var = add(I1, I2);
        } else if (I1.sign == -1 && I2.sign == -1) {
            I2.sign = 1;
            I1.sign = 1;
            var = sub(I2, I1);
        } else {
            if (compareBigInt(I1, I2) < 0) {
                I1.sign = 1;
                I2.sign = 1;
                var = sub(I2, I1);
                var.sign = -1;
            } else {
                LL* i1 = I1.data;
                LL* i2 = I2.data;
                int borrow = 0;
                while (i1 || i2) {
                    int x = (i1 ? i1->data : 0) - borrow;
                    int y = i2 ? i2->data : 0;
                    if (x < y) {
                        x += 10;
                        borrow = 1;
                    } else {
                        borrow = 0;
                    }
                    var.data = newNodeAtEnd(var.data, x - y);
                    var.length++;
                    if (i1) i1 = i1->next;
                    if (i2) i2 = i2->next;
                }
            }
        }
    }

    if (var.data)
        return truncate(var);
    return var;
}

// Function to check if a BigInteger is zero with appropriate sign
int iszero(SBI I) {
    if (I.sign == -1) {
        LL* ptr = I.data;
        while (ptr) {
            if (ptr->data != 0)
                return 0; // If any non-zero digit is found, it's not zero.
            ptr = ptr->next;
        }
        return 1; // All digits are zero, so it's a zero BigInteger.
    }
    return 0; // If the sign is positive, it's not zero.
}

// Function to divide two BigIntegers with appropriate signs
SBI div1(SBI I1, SBI I2) {
    SBI var, temp, quotient;
    var.sign = 1;
    var.length = 0;
    var.data = NULL;
    quotient.sign = 1;
    quotient.length = 0;
    quotient.data = NULL;

    if (!I1.data)
        printf("Error: I1 has not been initialized.\n");
    else if (!I2.data)
        printf("Error: I2 has not been initialized.\n");
    else if (iszero(I2))
        printf("Error: Division by zero is not allowed.\n");
    else if (iszero(I1))
        return I1; // 0 divided by anything is 0
    else {
        if (I1.sign == -1 && I2.sign == 1) {
            I2.sign = -1;
            var = div1(I1, I2);
        } else if (I1.sign == 1 && I2.sign == -1) {
            I2.sign = 1;
            var = div1(I1, I2);
        } else if (I1.sign == -1 && I2.sign == -1) {
            I1.sign = 1;
            I2.sign = 1;
            var = div1(I1, I2);
        } else {
            truncate(I1);
            truncate(I2);
            int compare = compareBigInt(I1, I2);
            if (compare < 0) {
                // If the dividend is smaller than the divisor, the result is 0
                return var;
            } else if (compare == 0) {
                // If both are equal, the result is 1
                var = addOne(var);
                return var;
            } else {
                SBI one;
                one.sign = 1;
                one.length = 1;
                one.data = newNode(1);
                while (compare >= 0) {
                    temp = I2;
                    int count = 1;
                    while (compareBigInt(I1, temp) >= 0) {
                        I1 = sub(I1, temp);
                        quotient = add(quotient, one);
                        compare = compareBigInt(I1, I2);
                        temp = mul(I2, intToBig(count++));
                    }
                }
            }
        }
    }

    if (I1.sign == -1 && I2.sign == -1)
        return truncate(quotient);
    else
        return var;
}

// Function to multiply two BigIntegers with appropriate signs
SBI mul(SBI I1, SBI I2) {
    SBI var, temp, result;
    var.sign = 1;
    var.length = 0;
    var.data = NULL;
    result.sign = 1;
    result.length = 0;
    result.data = NULL;

    if (!I1.data)
        printf("Error: I1 has not been initialized.\n");
    else if (!I2.data)
        printf("Error: I2 has not been initialized.\n");
    else if (iszero(I1) || iszero(I2))
        return var; // Multiplication by zero is zero
    else {
        if (I1.sign == -1 && I2.sign == 1) {
            I1.sign = 1;
            I2.sign = -1;
            var = mul(I1, I2);
        } else if (I1.sign == 1 && I2.sign == -1) {
            I1.sign = -1;
            I2.sign = 1;
            var = mul(I1, I2);
        } else if (I1.sign == -1 && I2.sign == -1) {
            I1.sign = 1;
            I2.sign = 1;
            var = mul(I1, I2);
        } else {
            truncate(I1);
            truncate(I2);

            LL* i2 = I2.data;
            int count = 0;
            while (i2) {
                temp = mulOne(I1, i2->data);
                for (int i = 0; i < count; i++) {
                    temp = mulByTen(temp);
                }
                result = add(result, temp);
                i2 = i2->next;
                count++;
            }
        }
    }

    return var.sign == I2.sign ? truncate(result) : sub(var, truncate(result));
}


