## Translate CLI tool

### The default language is PT-BR if you want different language change the line 50 to your language

### This tool use deepl api key for the translate so you need that

### You can store the key in a file(HOME/.deep_cli) or set the env in our shell

### If you want to compile(i recommend do that) your own version, dont forget to link the libcurl
### Example:
```bash
    gcc main.c parse.c response.c -lcurl -o deep-cli
```
