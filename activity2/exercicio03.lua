--EXERCICIO 03 DA LISTA 02 DE ANÁLISE DE ALGORITMOS
-- Objetiva-se saber o lucro perdido na entrega e os itens não entregues por um conjunto de caminhões T com capacidade Ti

--Fábrica dos objetos de lógica
local Objects = function()
  local self = {}

  --Akosma implementation: https://github.com/akosma/CodeaSort/blob/master/QuickSort.lua
  -- Uma implementação comum do Quicksort, foi feita uma pequena alteração na regra de comparação somente, para que o algoritmo ordene o vetor com base em uma propriedade 'value' do objeto
  self.Quicksort = function()
    local self = {}

    local function partition(array, p, r)
      local x = array[r].value
      local i = p - 1
      for j = p, r - 1 do
        if array[j].value <= x then
          i = i + 1
          local temp = array[i]
          array[i] = array[j]
          array[j] = temp
        end
      end
      local temp = array[i + 1]
      array[i + 1] = array[r]
      array[r] = temp
      return i + 1
    end

    local function quicksort(array, p, r)
      p = p or 1
      r = r or #array
      if p < r then
        q = partition(array, p, r)
        quicksort(array, p, q - 1)
        quicksort(array, q + 1, r)
      end
    end

    self.sort = function(array,p,r)
      quicksort(array,p,r)
    end

    return self
  end

  -- FindTravellersPaths 
  -- entradas: caminhões, itens
  -- saídas: todos os objetos não armazenados em algum caminhão
  -- O algoritmo usa a estratégia gulosa para resolver o problema. A partir do lucro dividido pelo peso, é calculado o parâmetro que será usado para ordenar o vetor de itens. 
  --Na segunda etapa para cada caminhão, tenta-se armazenar o máximo possível de itens. Ao final restará os itens que não serão entregues e estes são devolvidos para o método principal
  self.FindTravellersPaths = function(trucks,items)
    for k,i in ipairs(items) do
      i.value = i.profit / i.weigth;
    end 
    local quick = self.Quicksort()
    quick.sort(items, 1, #items)
    local objects = items
    for k,t in ipairs(trucks) do
      local nonStoredObjects = {}      
      local totalWeigth = 0
      --t.destinations = {}
      for i = #objects,1,-1 do
        if (objects[i].weigth+totalWeigth <= t.limit) then
          --t.destinations[#t.destinations+1] = objects[i].destination
          totalWeigth = totalWeigth+objects[i].weigth 
        else
          nonStoredObjects[#nonStoredObjects+1] = objects[i]
        end
      end
      objects = nonStoredObjects
    end
    return objects
  end

  self.Item = function(weigth, profit, destination)
    local self = {};
    self.weigth = weigth;
    self.profit = profit;
    self.destination = destination;
    return self;
  end;  
  
  return self
end

--Objeto para entrada e saída de dados
local MyIO = function()
  local self = {}

  self.simpleQuestion = function(question,isNumber)
    print(question)
    if isNumber then
      return tonumber(io.read())
    else
      return io.read()
    end
  end

  self.howManyThings  = function(thing, f)
    local t = {}
    print("Informe o número de " .. thing .. "  para adicionar")
    for i = 1, tonumber(io.read()) do
      print(thing .. ": " .. i)
      t[i] = f()
    end
    return t
  end  

  self.print = function(elements,f,thing) 
    for i = 1,#elements do
      if thing ~= nil then 
        print("--- ".. thing .. " " .. i .. " ---")
      end
      f(elements[i])
    end
    print(" ")
  end

  return self
end

local main = function() 

  --Inicialização
  local o = Objects()
  local mio = MyIO()

  --Entradas
  local trucks = mio.howManyThings(
    "Caminhões",
    function() return {limit = tonumber(tonumber(io.read()))} end
  );

  local items = mio.howManyThings(
    "Itens",
    function() print("Peso e Lucro"); return o.Item(tonumber(io.read()),tonumber(io.read()),1) end
  ); 

  local nonDeliveredItems = o.FindTravellersPaths(trucks,items)

  -- Saídas
  print("Itens não entregues")

  mio.print(
    nonDeliveredItems,
    function(element) 
      for k,v in ipairs({{element.profit,"Lucro"}, {element.weigth,"Peso"}}) do        
        print(v[2],v[1])
      end
    end,
    "Item"
  )
  
  local totalLost = 0
  for i = 1,#nonDeliveredItems do
    totalLost = totalLost+nonDeliveredItems[i].profit
  end

  print("Total perdido: " .. totalLost)

end

main()