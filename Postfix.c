int Precedence(char x)
{
	if (x == '(')
		return 0;
	if (x == '+' || x == '-')
		return 1 ;
	if (x == '*' || x == '/' || x == '%')
		return 2;

	return 3;
}
void InfixtoPostfix(char infix[], char postfix[])
{
	Stack S;
	char x, token;
	int i=0, j=0;    //i-index of infix,j-index of postfix
	init(&S);
	for (i = 0; infix[i] != '\0'; i++)
	{
		token = infix[i];
		if (isalnum(token))
			postfix[j++] = token;
		else
			if (token == '(')
				Push(&S, '(');
			else
				if (token == ')')
					while ((x = Pop(&S)) != '(')
						postfix[j++] = x;
				else
				{
					while (Precedence(token) <= Precedence(top(&S)) && !isEmpty(&S))
					{
						x = Pop(&S);
						postfix[j++] = x;
					}
					Push(&S, token);
				}
	}

	while (!isEmpty(&S))
	{
		x = Pop(&S);
		postfix[j++] = x;
	}

	postfix[j] = '\0';
}
float Evaluate(char *Postfix)
{
	struct Stack S;
	char *p;
	float op1, op2, result;
	S.TOP = -1; 
	p = &Postfix[0];
	while (*p != '\0')
	{
		while (*p == ' ' || *p == '\t')
		{
			p++;
		}
		if (isdigit(*p))
		{
			int num = 0;
			while (isdigit(*p))
			{
				num = num * 10 + *p - 48;
				*p++;
			}
			Push(&S, num);
		}
		else
		{
			op1 = Pop(&S);
			op2 = Pop(&S);
			switch (*p)
			{
			case '+':
				result = op2 + op1;
				break;
			case '-':
				result = op2 - op1;
				break;
			case '/':
				result = op2 / op1;
				break;
			case '*':
				result = op2 * op1;
				break;
			default:
				printf("\nInvalid Operator");
				return 0;
			}
			Push(&S, result);
		}
		p++;
	}
	result = Pop(&S);
	return result;
}