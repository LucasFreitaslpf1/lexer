void lex(const char *input)
{
	const char *p = input;

	while (*p != '\0')
	{
		if (isspace(*p))
		{
			p++;
			continue;
		}

		// Identificadores e Palavras-chave
		if (isalpha(*p) || *p == '_')
		{
			char buffer[100];
			int i = 0;
			while (isalnum(*p) || *p == '_')
				buffer[i++] = *p++;
			buffer[i] = '\0';

			if (is_keyword(buffer))
				printf("KEYWORD:    %s\n", buffer);
			else
				printf("IDENTIFIER: %s\n", buffer);
			continue;
		}

		// Números (Int e Float tradicionais)
		if (isdigit(*p))
		{
			char buffer[100];
			int i = 0;
			bool is_float = false;
			while (isdigit(*p) || (*p == '.' && !is_float))
			{
				if (*p == '.')
					is_float = true;
				buffer[i++] = *p++;
			}
			buffer[i] = '\0';
			printf("%s:       %s\n", is_float ? "FLOAT" : "INT", buffer);
			continue;
		}

		// Operadores e Símbolos (simplificado)
		if (ispunct(*p))
		{
			// Checa operadores de 2 caracteres como ==, <=, +=, etc.
			if ((*p == '=' || *p == '!' || *p == '<' || *p == '>' || *p == '+' || *p == '-' || *p == '*' ||
				 *p == '/') &&
				*(p + 1) == '=')
			{
				printf("OPERATOR:   %c%c\n", *p, *(p + 1));
				p += 2;
			}
			else
			{
				printf("SYMBOL:     %c\n", *p);
				p++;
			}
			continue;
		}
		p++;
	}
}
