# Definicje

## Grupa

Grupa to zbiór $G$ wraz z działaniem $\cdot$ spełniający następujące aksjomaty:
1. **Działanie jest określone**: $\forall a, b \in G: a \cdot b \in G$
2. **Działanie jest łączne**: $\forall a, b, c \in G: a \cdot (b \cdot c) = (a \cdot b) \cdot c$
3. **Istnieje element neutralny**: $\exists e \in G: \forall a \in G: a \cdot e = e \cdot a = a$
4. **Istnieje element odwrotny**: $\forall a \in G: \exists a^{-1} \in G: a \cdot a^{-1} = a^{-1} \cdot a = e$

## Podgrupa

Zbiór $H$ grupy $G$ jest podgrupą grupy $G$ jeśli:
1. **$H$ jest zamknięty na działanie**: $\forall a, b \in H: a \cdot b \in H$
2. **$H$ jest zamknięty na łączność**: $\forall a, b \in H: a \cdot b \in H$
3. **$H$ ma element neutralny**: $e \in H$
4. **$H$ jest zamknięty na odwrotność**: $\forall a \in H: a^{-1} \in H$

Wystarczy sprawdzić, że $H$ jest zamknięty na działanie i odwrotność.

## Podgrupa Normalna

Podgrupa $H$ grupy $G$ jest normalna w $G$ jeśli:
1. **$H$ jest podgrupą grupy $G$**:
   - **$H$ jest zamknięty na działanie**: $\forall a, b \in H: a \cdot b \in H$
   - **$H$ ma element odwrotny**: $\forall a \in H: a^{-1} \in H$
2. **$H$ jest zamknięty na przekształcenie koniugacyjne**: $\forall a \in G: aHa^{-1} = H$

## Homomorfizm Grup

Homomorfizm grup to funkcja $f: G \to H$ spełniająca warunek:
$$f(a \cdot b) = f(a) \cdot f(b)$$

## Jądro Homomorfizmu

Jądro homomorfizmu to zbiór elementów grupy $G$ przekształconych przez homomorfizm $f$ na element neutralny grupy $H$:
$$\ker f = \{a \in G: f(a) = e_H\}$$

## Obraz Homomorfizmu

Obraz homomorfizmu to zbiór elementów grupy $H$ przekształconych przez homomorfizm $f$ z grupy $G$:
$$\text{Im} f = \{f(a) \in H: a \in G\}$$

## Rząd Elementu Grupy

Rząd elementu grupy $G$ definiujemy jako:
$$\text{ord}(a) = \min\{n \in \mathbb{N}: a^n = e\}$$

Jeżeli taki $n$ nie istnieje, to element $a$ ma nieskończony rząd.

## Generator Grupy

Element $a$ grupy $G$ jest generatorem grupy $G$ jeśli:
$$\forall b \in G: \exists n \in \mathbb{Z}: b = a^n$$

## Warstwa Grupy

Warstwą grupy $G$ względem podgrupy $H$ definiujemy jako:
1. **Lewą warstwę**: $aH = \{a \cdot h: h \in H\}$
2. **Prawą warstwę**: $Ha = \{h \cdot a: h \in H\}$
3. **Warstwę dwustronną**: $aH = Ha$

## Grupa Cykliczna

Grupa $G$ jest grupą cykliczną jeśli istnieje taki element $a \in G$, że:
$$G = \{a^n: n \in \mathbb{Z}\}$$
 
Czyli grupa $G$ jest generowana przez **jeden** element $a$.

## Grupa Dihedralna

Grupa dihedralna $D_n$ to grupa symetrii $n$-kąta foremnego.

## Grupa Ilorazowa

Grupa ilorazowa $G/H$ grupy $G$ względem podgrupy normalnej $H$ to zbiór warstw grupy $G$ względem $H$ z działaniem:
$$(aH) \cdot (bH) = (a \cdot b)H$$

## Pierścień

Pierścień to zbiór $R$ wraz z dwoma działaniami $+$ i $\cdot$ spełniający następujące aksjomaty:
1. **$R$ jest grupą abelową**: $(R, +)$ jest grupą abelową
2. **Działanie $\cdot$ jest łączne**: $\forall a, b, c \in R: a \cdot (b \cdot c) = (a \cdot b) \cdot c$
3. **Zachodzi rozdzielność mnożenia względem dodawania**: $\forall a, b, c \in R: a \cdot (b + c) = a \cdot b + a \cdot c$ i $(a + b) \cdot c = a \cdot c + b \cdot c$

## Pierścień Odwracalny

Element $a$ pierścienia $R$ jest odwracalny jeśli istnieje taki element $b \in R$, że:
$$a \cdot b = b \cdot a = 1$$

Pierścień elementów odwracalnych oznaczamy jako $R^*=\{a \in R: a \text{ jest odwracalny}\}$

## Podpierścień

Podpierścieniem pierścienia $R$ jest zbiór $S \subseteq R$ wraz z działaniami $+$ i $\cdot$ takimi, że:
1. **$S$ jest zamknięty na dodawanie**: $\forall a, b \in S: a + b \in S$
2. **$S$ jest zamknięty na mnożenie**: $\forall a, b \in S: a \cdot b \in S$

## Homomorfizm Pierścieni

Homomorfizm pierścieni to funkcja $f: R \to S$ spełniająca warunki:
1. **$f$ jest homomorfizmem grup**: $f(a + b) = f(a) + f(b)$
2. **$f$ jest homomorfizmem pierścieni**: $f(a \cdot b) = f(a) \cdot f(b)$

## Ideał

Ideałem pierścienia $R$ jest zbiór $I \subseteq R$ spełniający warunki:
1. **$I$ jest podgrupą grupy abelowej**: $(I, +)$ jest podgrupą grupy abelowej
2. **$I$ jest zamknięty na mnożenie**: $\forall a, b \in I: a \cdot b \in I$
3. **$I$ jest zamknięty na dodawanie**: $\forall a, b \in I: a + b \in I$
4. **$I$ jest zamknięty na mnożenie przez elementy pierścienia**: $\forall a \in I, r \in R: a \cdot r \in I$ i $r \cdot a \in I$

## Ideał Główny

Ideałem głównym pierścienia $R$ generowanym przez element $a \in R$ jest zbiór:
$$\langle a \rangle = \{a \cdot r: r \in R\}$$

## Pierścień Ilorazowy

Pierścień ilorazowy $R/I$ pierścienia $R$ względem ideału $I$ to zbiór warstw pierścienia $R$ względem ideału $I$ z działaniami:
$$(a + I) + (b + I) = (a + b) + I$$
$$(a + I) \cdot (b + I) = (a \cdot b) + I$$

# Twierdzenia

## Twierdzenie Lagrange'a

Jeśli $G$ jest grupą skończoną, a $H$ jest podgrupą grupy $G$, to rząd grupy $H$ dzieli rząd grupy $G$.
$$|G| = |H| \cdot [G:H]$$
Lub inaczej
$$|H| | |G|$$

## Chińskie Twierdzenie o Resztach

Jeśli $m_1, m_2, \ldots, m_n$ są parami względnie pierwszymi liczbami całkowitymi, to układ kongruencji:
$$\begin{cases} x \equiv a_1 \pmod{m_1} \\ x \equiv a_2 \pmod{m_2} \\ \vdots \\ x \equiv a_n \pmod{m_n} \end{cases}$$
ma dokładnie jedno rozwiązanie modulo $m_1 \cdot m_2 \cdot \ldots \cdot m_n$.

## Twierdzenie Eulera - Fermata

Dla dowolnej liczby całkowitej $a$ względnie pierwszej z $n$ zachodzi:
$$a^{\varphi(n)} \equiv 1 \pmod{n}$$
