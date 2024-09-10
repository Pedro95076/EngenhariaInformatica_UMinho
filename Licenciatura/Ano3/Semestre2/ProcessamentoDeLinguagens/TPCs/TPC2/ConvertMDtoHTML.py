import re

def conv_heading(input: str) -> str:
    pattern = r"\s(#{1,3})\s(\w*)$" # NOTA: meter dentro de parêntesis secções, permite que grupos sejam separados na função group!!!!
    res = re.sub(pattern, lambda x: f"<h{len(x.group(1))}>{x.group(2)}</h{len(x.group(1))}>",input)
    return res

def conv_bold(input: str) -> str:
    pattern = r"\*\*(.*?)\*\*" # sem o ? só pega no primeiro e último <b> que aparecem
    res = re.sub(pattern, lambda x: f"<b>{x.group(1)}</b>",input)
    return res

def conv_italic(input: str) -> str:
    pattern = r"\*(.*?)\*"
    res = re.sub(pattern, lambda x: f"<i>{x.group(1)}</i>",input)
    return res

def conv_num_list(input: str) -> str:
    pattern = r"\s*(\d+)\.\s*(.*)\n?" # é preciso incluir o número em grupo também, para detetar todas as linhas direito
    
    res = "<ol>\n"
    matches = re.findall(pattern,input)
    for match in matches:
        res += f"   <li>{match[1]}</li>\n"
    res += "</ol>"
    return res

def conv_link(input: str) -> str:
    pattern = r"\[([^\]]+)\]\(([^\)]+)\)" # por qualquer razão, em vez de fazer [^\]] podia também fazer [^\\] ????
    res = re.sub(pattern, lambda x: f'<a href="{x.group(2)}">{x.group(1)}</a>', input)
    return res

def conv_image(input: str) -> str:
    pattern = r"!\[([^\]]+)\]\(([^\)]+)\)"
    res = re.sub(pattern, lambda x: f'<img src="{x.group(2)}" alt="{x.group(1)}"/>', input)
    return res

def main():
    print(conv_heading(" ### Exemplo"))
    print(conv_bold("Este é um **exemplo** ... **exemplo2** ..."))
    print(conv_italic("Este é um *exemplo* ... *exemplo2* ..."))
    print(
        conv_num_list(
        f"""
            1. Primeiro item
            2. Segundo item
            3. Terceiro item""")
    )
    print(conv_link("Como pode ser consultado em [página da UC](http://www.uc.pt) ..."))
    print(conv_image("Como se vê na imagem seguinte: ![imagem dum coelho](http://www.coellho.com) ..."))
    

if __name__ == "__main__":
    main()
