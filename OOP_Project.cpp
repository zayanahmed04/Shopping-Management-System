#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <cmath>
#include <cctype>
using namespace std;

class Order;
class Checkout;
class Category;
class Inventory;
class Cart;
class Admin{
    string email;
public:
    Admin(){}
    Admin(string email):email(email){}
    void ManageCategories(vector<Category>& categories);
    void ManageProducts(Category& category, Inventory& Inventory);
    void ManageInventory(Inventory& inventory, vector<Category>& categories, Order& order);
    void ManageTaxation(Order& order);
    void view(vector<Category>& categories, Inventory& inventory, Order& order);
};
class Customer{
    int CustomerID;
    string CustomerName, CustomerPhone, CustomerEmail, CustomerAddress, CustomerPass;
public:
    friend class Order;
    Customer(){}
    Customer(string custname, string custphone, string custemail, string custaddress, string custpass) 
    :CustomerName(custname), CustomerPhone(custphone), CustomerEmail(custemail), CustomerAddress(custaddress), CustomerPass(custpass){}
    Customer(string custname, string custpass):CustomerName(custname), CustomerPass(custpass){}
    bool CheckLoginStatus(Customer &c, Admin& admin, Inventory& inventory, vector<Category>& categories, Order& order){
        const string constemail = "123";
        const string password = "123";
        int option;
        while(1){
            cout << "1. Sign up\n2. login (admin only)\nYour choice : ";
            cin >> option;
            if(option >= 1 && option <= 2){
                system("cls");
                break;
            }
            system("cls");
            cout << "Invalid choice!" << endl;
        }
        string name, email, phone, address, pass, repass;
        bool flag = false;
        if(option == 1){
            cin.ignore();           
            while(1){
                cout << "Enter your Fullname : ";
                getline(cin,name);
                if(ValidateName(name)){
                    break;
                }
            }
            while(1){
                cout << "Enter your phone no. (03XX-XXXXXXX) : ";
                getline(cin,phone);
                if(Validatephone(phone)){
                    break;
                }
            }
            while(1){
                cout << "Enter your current residential address : ";
                getline(cin,address);
                if(ValidateAddress(address)){
                    break;
                }
            }
            while(1){
                cout << "Enter your email : ";
                getline(cin,email);
                if(ValidateEmail(email)){
                    break;
                }
            }
            bool authenticated = false;
            cout << "Enter password (Must be 8 characters minimum with special characters) : ";
            getline(cin,pass);
            if(CheckPasswordAuthentication(pass)){
                system("cls");
                cout << "Signup successful!" << endl;
            }
            if(displayinfo(name,phone,email,address)){
                c = Customer(name,phone,email,address,pass);
                system("cls");
                cout << "Your account has been successfully created!" << endl;
            }
            else{
                while(1){
                    if(!Checkinfo(name,phone,address,email)){
                        break;
                    }
                }
                cout << "This is the final information stored : " << endl;
                displayfinalinfo(name,phone,email,address);
                system("cls");
                c = Customer(name,phone,email,address,pass);
            }
        }
        else{
            fflush(stdin);
            cout << "\nEnter your Email : ";
            getline(cin,email);
            cout << "Enter your password : ";
            getline(cin,pass); 
            if(email == constemail && pass == password){
                system("cls");
                cout << "GREETINGS DEAR ADMIN !\n" << endl;
                admin.view(categories,inventory,order);
                return 1;
            }       
            else{
                cout << "You are not an admin!\nPlease signup" << endl;
                CheckLoginStatus(c,admin,inventory,categories,order);
            }
            
        }
    }
    bool ValidateName(const string& name){
        if (name.empty()) {
            system("cls");  
            cout << "You haven't entered anything!" << endl;
            return false;
        }
        bool hasSpace = false;
        bool lastCharWasSpace = false;
        for (int i = 0; i < name.size(); ++i) {
            if (!isalpha(name[i]) && name[i] != ' ') {
                system("cls");  
                cout << "Please enter alphabets only!" << endl;
                return false;
            }

            if (name[i] == ' ') {
                if (i == 0 || i == name.size() - 1 || lastCharWasSpace) {
                    system("cls");  
                    cout << "Please enter a valid full name with no leading, trailing, or consecutive spaces!" << endl;
                    return false;
                }
                hasSpace = true;
                lastCharWasSpace = true;
            } else {
                lastCharWasSpace = false;
            }
        }
        if (!hasSpace) {
            system("cls");  
            cout << "Please enter your full name!" << endl;
            return false;
        }
        system("cls");  
        return true;
    }
    bool Validatephone(const string& p){
        //dash hona chahiye beech mei
        //numbes hon 0-9
        if (p.empty()) {
            system("cls");  
            cout << "You haven't entered anything!" << endl;
            return false;
        }
        for(int i = 0 ; i < p.size() ; i++){
            if(i==4){
                continue;
            }
            if(!isdigit(p[i])){ //yahan pe inki ascii values daaldena
                system("cls");  
                cout << "Please enter only numbers!" << endl;
                return false;
            }
        }
        if(p[0] != 48 || p[1] != 51 || p[4] != 45){
            system("cls");
            cout << "Please follow the phone number format!" << endl;
            return false;
        }
        if(p.size() != 12){ 
            system("cls");  
            cout << "Insufficient phone number limit\nPlease enter 11 digit phone number!" << endl;
            return false;
        }
        system("cls");  
        return true;
    }
    bool ValidateAddress(const string& address) {
        if (address.empty()) {
            system("cls");
            cout << "You haven't entered anything!" << endl;
            return false;
        }

        bool lastCharWasSpace = false;
        bool validCharacterFound = false;

        for (size_t i = 0; i < address.size(); ++i) {
            char ch = address[i];

            if (isalnum(ch) || ch == ',' || ch == '-' || ch == ' ') {
                validCharacterFound = true;

                if (ch == ' ') {
                    if (i == 0 || i == address.size() - 1 || lastCharWasSpace) {
                        system("cls");
                        cout << "Please enter a valid address with no leading, trailing, or consecutive spaces!" << endl;
                        return false;
                    }
                    lastCharWasSpace = true;
                } else {
                    lastCharWasSpace = false;
                }
            } else {
                system("cls");
                cout << "Please enter a valid residential address containing only letters, numbers, spaces, commas, or dashes!" << endl;
                return false;
            }
        }

        if (!validCharacterFound) {
            system("cls");
            cout << "Please enter a valid residential address!" << endl;
            return false;
        }
        system("cls");
        return true;
    }
    bool ValidateEmail(const string& email) {
        if (email.empty()) {
            system("cls");
            cout << "You haven't entered anything!" << endl;
            return false;
        }

        bool hasAt = false;
        bool hasDot = false;
        size_t atIndex = 0;

        // Check if email contains valid characters and exactly one '@'
        for (size_t i = 0; i < email.size(); i++) {
            if (email[i] == ' ') {
                system("cls");
                cout << "Please enter a valid email with no spaces!" << endl;
                return false;
            } else if (email[i] == '@') {
                if (hasAt) {  // More than one '@'
                    system("cls");
                    cout << "Invalid email format! Only one '@' allowed." << endl;
                    return false;
                }
                hasAt = true;
                atIndex = i;
            } else if (email[i] == '.') {
                hasDot = true;
            } else if (!isalnum(email[i]) && email[i] != '.' && email[i] != '_') {
                system("cls");
                cout << "Invalid character found in the email!" << endl;
                return false;
            }
        }

        if (!hasAt || !hasDot) {
            system("cls");
            cout << "Invalid email format! Must contain both '@' and '.'" << endl;
            return false;
        }

        // Extract domain and check if it's in the allowed list
        string domain = email.substr(atIndex + 1);
        string allowedDomains[] = {"hotmail.com", "yahoo.com", "gmail.com", "outlook.com"};

        bool domainIsValid = false;
        for (const string& allowedDomain : allowedDomains) {
            if (domain == allowedDomain) {
                domainIsValid = true;
                break;
            }
        }

        if (!domainIsValid) {
            system("cls");
            cout << "The domain is not valid!" << endl;
            return false;
        }
        system("cls");
        return true;
    }

    void displayfinalinfo(string &name, string &phone, string &email, string &address){
        cout << "Name : "<< name << "\nPhone : " << phone << "\nEmail : " << email << "\nAddress : "<< address <<endl;
    }
    bool displayinfo(string name, string phone, string email, string address){
        int option;
        cout << "Is your entered information correct ?" << endl;
        cout << "Name : "<< name << "\nPhone : " << phone << "\nEmail : " << email << "\nAddress : "<< address <<endl;
        cout << "Enter 1 to continue and 0 to edit your information : ";
        cin >> option;
        system("cls");
        return option;
    }
    bool Checkinfo(string& name, string& phone, string& address, string& email){
        int option;
        //system("cls");
        cout << "What info you wish to modify?\n1. Name\n2. Phone\n3. Address\n4. Email\n5. Exit\nYour choice : ";
        fflush(stdin);
        cin >> option;
        cin.ignore();
        switch(option){
            case 1 :
                while(1){
                    cout << "Enter correct Name : ";
                    getline(cin,name);
                    if(ValidateName(name)){
                        break;
                    }
                }
                system("cls");
                cout << "Name updated successfully!" << endl;
                break;
            case 2 :
                while(1){
                    cout << "Enter correct Phone : ";
                    getline(cin,phone);
                    if(Validatephone(phone)){
                        break;
                    }
                }
                system("cls");
                cout << "Phone updated successfully!" << endl;
                break;
            case 3 :
                while(1){
                    cout << "Enter correct Address : ";
                    getline(cin,address);
                    if(ValidateAddress(address)){
                        break;
                    }
                }
                system("cls");
                cout << "Address updated successfully!" << endl;
                break;
            case 4 :
                while(1){
                    cout << "Enter correct Email : ";
                    getline(cin,email);
                    if(ValidateEmail(email)){
                        break;
                    }
                }
                system("cls");
                cout << "Email updated successfully!" << endl;
                break;
            case 5 :
                system("cls");
                return 0;
            default:
                cout << "invalid choice!\nPlease enter again" << endl;
        }
        return 1;
    }
    bool CheckSpecialCharacter(string& pass){
        bool hasSpecial = false;
        for(int i = 0 ; i < pass.size() ; i++){
            if(pass[i] == ' '){
                cout << "Space is not allowed in passwords!";
                return 0;
            }
            if((pass[i]>=33 && pass[i] <= 47) || (pass[i]>=58 && pass[i] <= 64) || (pass[i]>=91 && pass[i] <= 96) || (pass[i]>=123 && pass[i] <= 126)){
                hasSpecial = true;
            } 
        }
        if(!hasSpecial){
            cout << "Password does not have a special character!" << endl;
            return 0;
        }
        return 1;
    }
    bool CheckPasswordAuthentication(string& pass){
        string repass;
        while(1){
            if(pass.size() < 8){
                fflush(stdin);
                cout << "The password lenght is insufficient!";
                cout << "\nEnter password (Must be above 8 characters in lenght) : ";
                //cin >> pass;
                getline(cin,pass);
                continue;
            }
            if(!CheckSpecialCharacter(pass)){
                cout << "\nEnter password (Must be above 8 in lenght with minimum 1 special characters) : ";         
                getline(cin,pass);
                continue;
            }
            cout << "Enter password again : ";
            cin >> repass;
            if(pass != repass){
                cout << "Passwords Donot match!\nEnter them again:" << endl;
                cout << "Enter password (Must be above 8 in lenght with minimum 1 special character) : ";
                cin.ignore();
                getline(cin,pass);
                continue;
            }
            else{
                break;
            }
        }
        return 1;
    }
    void display()const{
        cout << "Name : " << CustomerName << endl;
        cout << "Phone : " << CustomerPhone << endl;
        cout << "Email : " << CustomerEmail << endl;
        cout << "Address : " << CustomerAddress << endl;
    }
};

class Product{
    int ProductPrice, ProductQuantity, ProductNumber, catnum, tempquantity;
    string ProductName, Description, ProductID;
public:
    friend class Cart;
    friend class Admin;
    Product(){}
    Product(int prodid, int productquantity, string productid, string prodname, int prodprice, string proddes)
    :ProductNumber(prodid), ProductQuantity(productquantity), ProductID(productid), ProductName(prodname), ProductPrice(prodprice), Description(proddes), tempquantity(productquantity){
         if(Description.size() > 24){
            string temp;
            cout << "\nWarning description greater than 24 characters!" << endl << endl;
            for(int i = 0 ; i < 25 ; i++){
                temp[i] = proddes[i];
            } 
            Description = temp;
        }
    }
     Product(int productnumber,int productquantity, string prodname, int prodprice, string proddes)
    :ProductNumber(productnumber),ProductQuantity(productquantity), ProductName(prodname), ProductPrice(prodprice), Description(proddes){
        if(Description.size() > 24){
            string temp;
            cout << "\nWarning description greater than 24 characters!" << endl << endl;
            for(int i = 0 ; i < 25 ; i++){
                temp[i] = proddes[i];
            } 
            Description = temp;
        }
    }
    int get_newproquantity()const{
        return tempquantity;
    }
    void set_newprodquantity(int quantity){
        tempquantity = quantity;
    }
    void display()const{
        cout << "Product Number : " << ProductNumber << endl;
        cout << "Product Name : " << ProductName << endl;
        cout << "Product Price : " << ProductPrice << endl;
        cout << "Product Description : " << Description << endl;
    }
    void displayWithQuantity()const{
        cout << "Product ID : " << ProductID << endl;
        cout << "Product Name : " << ProductName << endl;
        cout << "Product Price : " << ProductPrice << endl;
        cout << "Product Description : " << Description << endl;
        cout << "Quantity : " << ProductQuantity << endl;
    }
    int get_productprice()const{
        return ProductPrice;
    }
    int get_productquantity()const{
        return ProductQuantity;
    }
    string get_ProductId(){
        return ProductID;
    }
    string get_Productname()const{
        return ProductName;
    } 
    string get_Productdescription(){
        return Description;
    }
    void set_ProductQuantity(int quantity){
        this->ProductQuantity = quantity;
    }
    void set_Productprice(int price){
        this->ProductPrice = price;
    }
    void set_Productname(const string& name){
        this->ProductName = name;
    }
    void set_Productdescription(const string& des){
        this->Description = des;
    }
    void setProductid(string Productid){
        this->ProductID = Productid;
    }
    void set_productnumber(int prodnum){
        this->ProductNumber = prodnum;
    }
};

class Category{
    vector<Product> products;
    int Cat_id;
    string name;
public:
    Category(){}
    Category(string name, int id):name(name),Cat_id(id){}
    string get_name(){
        return name;
    }
    void static set_CategoryNumber(vector<Category>& categories){
        for(int i = 0 ; i < categories.size() ; i++){
            categories[i].Cat_id = i+1;
        }
    }
    void set_Productnumber(vector<Product>& products){
        for(int i = 0 ; i < products.size() ; i++){
            products[i].set_productnumber(i+1);
        }
    }                                                   //this is done to counter deletion of a product and reassign product number
    bool checkDuplication(vector<Product>& product,const string& str){
        for(int i = 0 ; i < product.size() ; i++){
            if(product[i].get_Productname() == str || product[i].get_Productdescription() == str || product[i].get_ProductId() == str ){
                return 0;
            }
        }
        return 1;
    }
    void update(vector<Product>& products){
        int choice, newval, prodid;
        string new_value, temp;
        temp.resize(23);
       while(1){
            system("cls");
            for(const auto& products : products){
                products.display();
                cout << endl;
            }
            while(1){
                cout << "Enter Product number : ";
                cin >> prodid;    
                if(prodid > 0 && prodid <= products.size()){
                    break;
                }
                cout << "Invalid product number!" << endl;
            }
            
            cout << "1. Change Product name\n2. Change Product price\n3. Change Product description\n4. Change Product quantity\n5. Exit\nYour choice" << endl;
            cin >> choice;
            fflush(stdin);
            switch (choice){
            case 1:
                cout << "Enter new Product Name : ";
                getline(cin, new_value);
                if(!checkDuplication(products, new_value)){
                    cout << "Duplication of product name not allowed!" << endl;
                    break;
                }
                products[prodid-1].set_Productname(new_value);
                break;
            case 2:
                cout << "Enter new Product price : ";
                cin >> newval;
                if(newval > 0){
                    products[prodid-1].set_Productprice(newval);
                }
                break;   
            case 3:
                cout << "Enter new Product description : ";
                getline(cin, new_value);
                if(!checkDuplication(products, new_value)){
                    cout << "Duplication of product description not allowed!" << endl;
                    break;  
                }
                if(new_value.size() > 24){
                    cout << "Warning description greater than 24 characters" << endl;
                    for(int i = 0 ; i < 23 ; i++){
                        temp[i] = new_value[i];
                    } 
                }
                products[prodid-1].set_Productdescription(temp);
                cout << "New Description set successfully!" << endl;
                break;  
            case 4:
                cout << "Enter new Product quantity : ";
                cin >> newval;
                 if(newval > 0){
                    products[prodid-1].set_ProductQuantity(newval);
                    products[prodid-1].set_newprodquantity(newval);
                    break;
                }
                cout << "Please enter Product quantity greater than 0!" << endl;
                break;  
            case 5:
                system("cls");
                return;
            default:
                cout << "Wrong Choice! Enter again" << endl;
                break;  
            }
        }
    } 
    void addProduct(vector<Product>& products){
        string pname, description;
        int quantity, price, prodid;
        fflush(stdin);
        while(1){
            cout << "Enter Product name : ";
            getline(cin,pname);
            if(checkDuplication(products,pname)){
                break;
            }
            cout << "Duplication of name not allowed!" << endl;
        }
        while(1){
            cout << "Enter Product price : ";
            cin >> price;
            if(price > 0){
                break;
            }
            cout << "Product price should be greater than 0 !" << endl;

        }
        while(1){
            cout << "Enter Product quantity : ";
            cin >> quantity;
            if(quantity > 0){
                break;
            }
            cout << "Product quantity should be greater than 0 !" << endl;
        }
        fflush(stdin);
        while(1){
            cout << "Enter Product description : ";
            getline(cin,description);
            if(checkDuplication(products,pname)){
                break;
            }
        }
        prodid = products.size()+1;
        products.push_back(Product(prodid,quantity,pname,price,description));
        products[prodid-1].set_newprodquantity(quantity);
        system("cls");
        cout << "Product added successfully!" << endl;
    }
    void DeleteProduct(vector<Product>& products){
        int prodid;
        if(products.size() == 0){
            cout << "No products to delete!" << endl;
            return;
        }
        for(int i = 0 ; i < products.size() ; i++){
            products[i].display();
            cout << endl;
        }
        while(1){
            cout << "Enter Product number : ";
            cin >> prodid;
            if(prodid <= products.size() && prodid > 0){
                break;
            }
            cout << "You have incorrect product number!" << endl;
        }
        products.erase(products.begin()+prodid-1);
        set_Productnumber(products);
        system("cls");
        cout << "Product deleted successfully!" << endl;
    }
    Product& getProductByID(const string& Productid){
        for(int i = 0 ; i < products.size() ; i++){
            if(products[i].get_ProductId() == Productid){
                return products[i];
            }
        }
    }
    void addDefaultCategories(vector<Category>& categories){
        categories.push_back(Category("Home and Lifestyle", 1));
        categories.push_back(Category("Electronic Devices", 2));
        categories.push_back(Category("Electronic Accessories", 3));
        categories.push_back(Category("TV and Home Appliances", 4));
        categories.push_back(Category("Sports and Outdoor", 5));
        categories.push_back(Category("Men and Women Fashion", 6));
    }
    void InitializeAllProducts(vector<Category>& categories){
        //Adding Products to all categories
        categories[0].products.push_back(Product(1,10,"HaL1","Microwave",500,"Microwave by dawlance"));
        categories[0].products.push_back(Product(2,20,"HaL2","Chair",50,"Chair hai jaani kya hfgd"));
        categories[1].products.push_back(Product(1,30,"ED1","Oven",1000,"Microwave by dawlance"));
        categories[2].products.push_back(Product(1,40,"EA1","Doormat",1500,"Microwave by dawlance"));
        categories[3].products.push_back(Product(1,50,"TaHA1","Stove",2000,"Microwave by dawlance"));
        categories[4].products.push_back(Product(1,60,"SaO1","Bottle",2500,"Microwave by dawlance"));
        categories[5].products.push_back(Product(1,70,"MaWF1","Dispenser",3000,"Microwave by dawlance"));
    }
    void DisplayProducts(){ 
        for(int i = 0 ; i < products.size() ; i++){
            products[i].display();
            cout << endl;
        }
    }
    bool ChooseCategory(vector<Category>& categories, Cart& cart, Inventory& inventory, Checkout& check, Order& order, Customer& customer);
    void static addCategory(vector<Category>& categories){
        int cat_id,i=0,ans;
        bool duplicate = false;
        string catname;
        cin.ignore();
        while(1){   
            cout << "Enter new category Name : ";
            getline(cin,catname);
            while(i < categories.size()){
                if(categories[i].get_name() == catname){
                    cout << "No duplicate categories allowed!" << endl;
                    duplicate = true;
                    return;
                }
                i++;
            }
            if(!duplicate){
                break;
            }
        }
        cat_id = categories.size()+1;        
        categories.push_back(Category(catname,cat_id));
        while(1){
            cout << "Enter 1 to keep adding products and 0 to exit : ";
            cin >> ans;
            if(!ans){
                system("cls");
                break;
            }
            categories[cat_id-1].addProduct(categories[cat_id-1].get_ProductsInCategory());
        }
        system("cls");
        cout << "Category Successfully Added!" << endl;
    }
    void static deleteCategory(vector<Category>& categories){
        int cat_id;
        for(int i = 0 ; i < categories.size() ; i++){
            cout << i+1 <<". ";
            categories[i].display();
        }
        while(1){
            cout << "Enter category Id of category you wish to delete : ";
            cin >> cat_id;
            if(cat_id <= categories.size() && cat_id > 0){
                break;
            }
            cout << "Wrong category number entered!\nPlease try again" << endl;
        }
        categories.erase(categories.begin()+cat_id-1);
        Category::set_CategoryNumber(categories);
        system("cls");
        cout << "Category successfully deleted!" << endl;
    }
    void static Updatecategory(vector<Category>& categories){
        int index;
        string catname;
        for(int i = 0 ; i < categories.size() ; i++){
            cout << i+1 <<". ";
            categories[i].display();
        }
        while (1){
            cout << "Enter Category number of which you want to modify its Name : ";
            cin >> index;
            if(index <= categories.size() && index > 0){
                break;
            }
            cout << "Incorrect Category number entered!\nPlease try again" <<  endl;
        }       
        fflush(stdin);
        cout << "Enter new Name : ";
        getline(cin,catname);
        categories[index-1].name = catname;
        system("cls");
        cout << "Category Name Successfully Updated!" << endl;
    }
    void display()const{
        cout << "Category Name : " << name << endl; 
    }
    vector<Product>& get_ProductsInCategory(){
        return products;
    }
};

Category& getCategory(vector<Category>& categories){      
    int catnum;
    for(int i = 0 ; i < categories.size() ; i++){
        cout << i+1 <<". ";
        categories[i].display();
    }
    while(1){
        cout << "Enter Category number : ";
        cin >> catnum;
        if(catnum <=  categories.size() && catnum > 0){
            break;
        }
        cout << "Wrong category number! Please enter again";
    }
    return categories[catnum-1];
}
void Admin::ManageCategories(vector<Category>& categories){
    int choice;
    while(1){
        while (1){
            cout << "1. Add a category\n2. Delete a category\n3. Update category\n4. Exit\nYour choice : ";
            cin >> choice;
            if(choice > 0){
                break;
            }
            cout << "Invalid choice!" << endl;
        }        
        switch(choice){
            case 1:
                system("cls");
                Category::addCategory(categories);
                break;
            case 2:
                system("cls");
                Category::deleteCategory(categories);
                break;
            case 3:
                system("cls");
                Category::Updatecategory(categories);
                break;
            case 4:
            system("cls");
                return;
            default:
                cout << "Wrong choice! Please enter again" << endl;
        }
    }
}
void Admin::ManageProducts(Category& category, Inventory& inventory){
    int catnum, choice;
    while(1){
        while (1){ 
            cout << "1. Add a product\n2. Delete a product\n3. Modify product details\n4. Exit\nYour choice : ";
            cin >> choice;
            if(choice >=1 && choice <=4){
                break;
            }
            cout << "Invalid choice!" << endl;
        }
        switch (choice){
            case 1:
                system("cls");
                category.addProduct(category.get_ProductsInCategory());
                break;
            case 2:
                system("cls");
                category.DeleteProduct(category.get_ProductsInCategory());
                break;
            case 3:
                system("cls");
                category.update(category.get_ProductsInCategory());
                break;
            case 4:
                system("cls");
                return;
            default:
                break;
        }
    }    
}

class Inventory{
    vector<Category> Inventorycategories;
public:
    vector<Category>& get_InventoryCategories(){
        return Inventorycategories;
    }
    void set_InventoryCategories(vector<Category>& categories){
        Inventorycategories = categories;
    }
    void set_InventoryCategoriesToCategoriesNew(vector<Category>& categories){
        categories = Inventorycategories;
    }
    bool CheckProductAvailability(int catnum, int prodid, int quantity){
        if(quantity >
         Inventorycategories[catnum-1].get_ProductsInCategory()[prodid-1].get_newproquantity()){
            return false;
        }
        int remaining = Inventorycategories[catnum-1].get_ProductsInCategory()[prodid-1].get_productquantity()-quantity;
        Inventorycategories[catnum-1].get_ProductsInCategory()[prodid-1].set_ProductQuantity(remaining);
        return true;
    }
    int CheckProductAvailability(int catnum, string p_id, int quantity, int){     //to implement in logic of reassigning quantity
       for(int i = 0 ; i < Inventorycategories[catnum-1].get_ProductsInCategory().size() ; i++){
            if(Inventorycategories[catnum-1].get_ProductsInCategory()[i].get_ProductId() == p_id){
                int remaining = Inventorycategories[catnum-1].get_ProductsInCategory()[i].get_productquantity()-quantity;
                Inventorycategories[catnum-1].get_ProductsInCategory()[i].set_ProductQuantity(remaining);
            }
        }
    }
};

void Admin::view(vector<Category>& categories, Inventory& inventory, Order& order){
    int choice;
    bool valid = false;
    while(1){
        while (1){
            cout << "1. Manage Categories\n2. Manage Products\n3. Manage inventory\n4. Manage Taxation\n5. Exit\nYour choice : ";
            cin >> choice;
            if(choice >= 1 && choice <= 5){
                break;
            }
        }        
        switch(choice){
            case 1:
                system("cls");
                ManageCategories(categories);
                break;
            case 2:
                system("cls");
            cout << "Which Category you wish to modify products in?" << endl;
                ManageProducts(getCategory(categories), inventory);
                inventory.set_InventoryCategories(categories);
                break;
            case 3:
                system("cls");
                ManageInventory(inventory,categories,order);
                break;
            case 4:
                system("cls");
                ManageTaxation(order);
                break;
            case 5:
                system("cls");        
                return;
            default:
                cout << "Wrong choice! Please enter again" << endl;
        }
    }
}
void Admin::ManageInventory(Inventory& inventory, vector<Category>& categories, Order& order){
    int choice, catnum, prodid, quantity;
    string prodnum;
    cout << "1. Modify product quantity\n2. Exit\nYour choice : ";
    cin >> choice;
    while(1){
        switch(choice){
            case 1:
                cout << "Which Category you wish to modify products in?" << endl;
                for(int i = 0 ; i < inventory.get_InventoryCategories().size() ; i++){
                    cout << i+1 <<". ";
                    inventory.get_InventoryCategories()[i].display();
                }
                while(1){
                    cout << "Enter Category number : ";
                    cin >> catnum;
                    if(catnum <=  inventory.get_InventoryCategories().size() && catnum > 0){
                        break;
                    }
                    cout << "Wrong category number! Please enter again\n";
                }
                inventory.get_InventoryCategories()[catnum-1].DisplayProducts();
                int prodid;
                while(1){
                    cout << "Enter product number : ";
                    cin >> prodid;
                    if(prodid <= inventory.get_InventoryCategories()[catnum-1].get_ProductsInCategory().size() && prodid > 0){
                        break;
                    }
                    cout << "Wrong Product number! Please enter again\n" << endl;
                }   
                cout << "Current quantity : " << inventory.get_InventoryCategories()[catnum-1].get_ProductsInCategory()[prodid-1].ProductQuantity << endl;
                while(1){
                    cout << "Enter new product quantity : ";
                    cin >> quantity;
                    if(quantity > 0){
                        break;
                    }
                    cout << "Please enter quantity in range!" << endl;
                }
                inventory.get_InventoryCategories()[catnum-1].get_ProductsInCategory()[prodid-1].ProductQuantity = quantity;
                inventory.get_InventoryCategories()[catnum-1].get_ProductsInCategory()[prodid-1].tempquantity = quantity;
                inventory.set_InventoryCategoriesToCategoriesNew(categories);
                return;
            case 2:
                return;  
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

class Cart{
    int CustomerID, ProductID;
    vector<Product> CartProducts;
public:
    Cart(){}
    Cart(int custid, int prodid): CustomerID(custid), ProductID(prodid){}
    string get_initials(string& catname){
        string catinitials;
        catinitials += catname[0];
        for(int i  = 0 ; i < catname.size() ; i++){
            if(catname[i] == 32){
                catinitials += catname[i+1];
            }      
        }
        return catinitials;
    }
    string get_newProductid(string catname, string prodnum){
        string initials = get_initials(catname);
        return initials += prodnum;
    }

    void AddToCart(vector<Category>& categories, int catnum, Inventory& inventory){
        Product p_Quantity;
        string prodnum, Productid;
        int prodquantity, prodid;
        system("cls");
        while(1){
            cout << "Displaying category products below : " << endl;
            categories[catnum-1].DisplayProducts();
            cout << "Enter Product number : ";
            cin >> prodid;
            if(prodid <= categories[catnum-1].get_ProductsInCategory().size() && prodid != 0){
                break;
            }
            system("cls");
            cout << "Wrong product ID entered!" << endl;
        }
        while(1){
            cout << "Product quantity available : " << inventory.get_InventoryCategories()[catnum-1].get_ProductsInCategory()[prodid-1].get_productquantity() << endl;
            if(inventory.get_InventoryCategories()[catnum-1].get_ProductsInCategory()[prodid-1].get_productquantity()){
                cout << "\nEnter Product quantity : ";
                cin >> prodquantity;    
                if(prodquantity <= 0){
                    cout << "Quantity is not valid! Please enter again " << endl;
                    continue;
                }
            }
            else{
                system("cls");
                cout << "Sorry you cannot select more than max quantity!" << endl;
                return;
            }
            if(inventory.CheckProductAvailability(catnum, prodid, prodquantity)){
                break;
            }
            system("cls");
            cout << "Invalid Product Quantity!" << endl;
        }
        prodnum = to_string(prodid);
        Productid = get_newProductid(categories[catnum-1].get_name(), prodnum);
        if(!CartProducts.empty()){
            for(int i = 0 ; i < CartProducts.size() ; i++){
                if(CartProducts[i].ProductID == Productid){
                    CartProducts[i].ProductQuantity += prodquantity;
                    system("cls");
                    return;
                }
            }
        }
        categories[catnum-1].get_ProductsInCategory()[prodid-1].setProductid(Productid);
        p_Quantity = categories[catnum-1].getProductByID(Productid); 
        p_Quantity.ProductQuantity = prodquantity;
        p_Quantity.catnum = catnum;
        CartProducts.push_back(p_Quantity);
        system("cls");
        cout << "Product added to cart successfully!" << endl;
    }
    vector<Product>& get_Cartproducts(){
        return CartProducts;
    }
    void display(){
        for(int i = 0 ; i < CartProducts.size() ; i++){
            CartProducts[i].displayWithQuantity();
            cout << endl;
        }
    }
    void display(int){
        for(int i = 0 ; i < CartProducts.size() ; i++){
            cout << "Product number : "<< i+1 << endl;
            CartProducts[i].displayWithQuantity();
            cout << endl;
        }
    }
    void Delete_InCart(){
        system("cls");
        int index;
        if(CartProducts.empty()){
            cout << "Cart is already empty!" << endl;
            return;
        }
        display(1);
        while(1){
            cout << "Please enter Item's product number you wish to remove : " << endl;
            cin >> index;   
            if(index <= CartProducts.size() && index > 0){
                break;
            }
            cout << "incorrect Product number entered" << endl;
        }
        CartProducts.erase(CartProducts.begin()+index-1);
        system("cls");
        if(CartProducts.empty()){
            cout << "Your Cart is empty now!" << endl;
        }
    }
    void Update_InCart(Cart& cart, Inventory inventory, vector<Category>& categories){
        int index, quantity, choice;
        system("cls");
        display(1);
        while(1){
            cout << "Please enter Cart's product number you wish to modify quantity: " << endl;
            cin >> index;   
            if(index <= CartProducts.size() && index > 0){
                break;
            }
            cout << "incorrect Product number entered!" << endl;
        }
        const int qty = categories[cart.CartProducts[index-1].catnum-1].getProductByID(cart.CartProducts[index-1].ProductID).get_newproquantity();
        while(1){
            cout << "Current available quantity : " << qty << endl;
            cout << "Enter new quantity : ";
            cin >> quantity;
            if(quantity > 0 && quantity <= categories[cart.CartProducts[index-1].catnum-1].getProductByID(cart.CartProducts[index-1].ProductID).get_newproquantity()){                
                break;
            }
            if(quantity < 0){
                cout << "Entered quantity is below 0!\nPlease enter quantity greater than 0" << endl;
            }
            cout << "Enter quantity in range!" << endl;
        }
        
        while(1){
            cout << "Are your changes complete?\n1. Yes\n2. No\nYour choice : ";
            cin >> choice;
            if(choice <= 2 && choice >= 1){
                break;
            }
        }
        if(choice == 1){
            system("cls");
            CartProducts[index-1].set_ProductQuantity(quantity);
            //inventory.CheckProductAvailability(cart.CartProducts[index-1].catnum, cart.CartProducts[index-1].ProductID,quantity,1);
            //categories[cart.CartProducts[index-1].catnum-1].getProductByID(cart.CartProducts[index-1].ProductID).set_newprodquantity(quantity);
            return;
        }
        else{
            CartProducts[index-1].set_ProductQuantity(quantity);
            Update_InCart(cart,inventory,categories);
        }
       
    }
    void displayFormatted(){
        const int idWidth = 13;
        const int nameWidth = 20;
        const int descriptionwidth = 32;
        const int quantityWidth = 15;
        const int priceWidth = 17;
        const int totalWidth = 15;
       for (const auto& CartProducts : CartProducts){
            cout << "   ";
            cout << left << setw(idWidth) << CartProducts.ProductID
                << setw(nameWidth) << CartProducts.ProductName 
                << setw(descriptionwidth) << CartProducts.Description
                << setw(quantityWidth) << CartProducts.ProductQuantity
                << setw(priceWidth) << CartProducts.ProductPrice
                << setw(totalWidth) << CartProducts.ProductPrice * CartProducts.ProductQuantity
                << endl;
        }
    }
};

class Order{
    string ProductID, OrderID, CustomerID;
    float TaxPercent;
public:
    Order(){}
    Order(string prodid, string orderid, string custid)
    :ProductID(prodid), OrderID(orderid), CustomerID(custid){}
    void set_Tax(float tax){
        TaxPercent = tax;
    }
    float get_tax()const{
        return TaxPercent;
    }
    void GenerateBill(Cart& cart, Customer& customer, Checkout& checkout);
    string getCurrentDate() {              
        // Get the current time
        time_t now = time(nullptr);
        // Convert it to local time
        tm* localTime = localtime(&now);

        // Create a string stream to format the date
        ostringstream oss;
        oss << put_time(localTime, "%Y-%m-%d");
        return oss.str();
    }
    void set_CustID(const string& id){
        CustomerID = id;
    }
    void add(){}
    void view(){}
};

void Admin::ManageTaxation(Order& order){
        float tax;
        while(1){
            cout << "Enter tax rate in percentage (%) : ";
            cin >> tax;
            if(tax > 0){
                break;
            }
            cout << "Please enter tax rates greater than 0" << endl;
        }
        order.set_Tax(tax);
        cout << "Tax rate set successfully!" << endl;
    }
class Checkout{
    int CustomerID;
    string Cartnumber;
public:
    Checkout(){}
    Checkout(int custid, string cartnum):CustomerID(), Cartnumber(cartnum){} //isko dekhlena
    bool checkout(Cart& cart, Order& order, Customer& customer, Inventory& inventory, Checkout& checkout, vector<Category>& categories){
        int choice;
        cout << "\nHere is your cart below : " << endl;
        cart.display();
        cout << "Please choose from the below options!" << endl;
        while(1){
            while(1){
                cout << "1. Keep Shopping\n2. Manage Cart\n3. Generate Bill\nYour choice : ";
                cin >> choice;
                if(choice <= 3 && choice >= 1){
                    break;
                }
            }            
            switch (choice){
                case 1:
                    system("cls");
                    return 1;
                case 2:
                    system("cls");
                    ManageCart(cart,inventory,categories);
                    break;
                case 3:
                    system("cls");
                    order.GenerateBill(cart,customer,checkout);
                    return 0;
                default:
                    break;
            }
        }
    }
    void ManageCart(Cart& cart, Inventory& Inventory, vector<Category> categories){
        int choice;
        bool valid = false;
        while (1){
            while (1){
                cout << "1. Update quantity in cart\n2. Delete a product from cart\n3. Exit\nYour choice: ";
                cin >> choice;
                if(choice >= 1 && choice <= 3){
                    break;
                }
                cout << "Invalid choice!" << endl;
            }
            switch (choice){
                case 1:
                    cart.Update_InCart(cart,Inventory,categories);
                    break;
                case 2:
                    cart.Delete_InCart();
                    break;
                case 3:
                    system("cls");
                    return;
                default:
                    break;    
            }
        }
    }
    int bill(Cart& cart){
        int total = 0;
        for(int i = 0 ; i < cart.get_Cartproducts().size() ; i++){
            total += cart.get_Cartproducts()[i].get_productprice() * cart.get_Cartproducts()[i].get_productquantity(); 
        }
        return total;
    }
};

void Order::GenerateBill(Cart& cart, Customer& customer, Checkout& checkout){
        const int idWidth = 14;
        const int nameWidth = 28;
        const int descriptionwidth = 23;
        const int quantityWidth = 15;
        const int priceWidth = 17;
        const int totalWidth = 11;

        // Print header
        cout << "-------------------------------------------------------------------------------------------------------------"<< endl;
        cout << "\t\t\t\t\t    Zayan's Company" <<endl;
        cout << "\t  -----------------------------------------------------------------------------------------"<< endl;
        cout << "\t\t\t\t\t    Customer's Bill" << endl;
        cout << "-------------------------------------------------------------------------------------------------------------"<< endl;
        //yahan pe order number aur phir order date ayegi
        cout << "Order Date: " << getCurrentDate() << endl;
        cout << "-------------------------------------------------------------------------------------------------------------"<< endl;
        //yahan pe Customers info
        customer.display();
        cout << "-------------------------------------------------------------------------------------------------------------"<< endl;
        cout << "Items:" << endl;
        cout << "-------------------------------------------------------------------------------------------------------------"<< endl;
        //yahan pe sare cart items ayein ge
        cout << left << setw(idWidth) << "    ID" << setw(nameWidth) << "Product Name" << setw(descriptionwidth) << "Description" << setw(quantityWidth) << "Quantity" << setw(priceWidth) << "Unit Price" << setw(totalWidth) << "Total Price" << endl;
        cout << string(idWidth + nameWidth + descriptionwidth + quantityWidth + priceWidth + totalWidth  + 1, '-') << endl;
        cart.displayFormatted();
        cout << "-------------------------------------------------------------------------------------------------------------"<< endl;
        //Total ayega, Tax applied ayega
        cout << "Sub-total : Rs. " << checkout.bill(cart) << endl;
        cout << "Tax applied (GST) : " << TaxPercent << "%" << endl;            //YAHAN TAX APPLIED AYEGA    
        cout << "-------------------------------------------------------------------------------------------------------------"<< endl;
        //grand total ayega yahn
        cout << "Grant total : Rs. " << ceil(((checkout.bill(cart) * TaxPercent)/100) + checkout.bill(cart)) << endl;
        cout << "-------------------------------------------------------------------------------------------------------------"<< endl;
        //payment info ayegi k kis tarhan pay kiya, Aur payment status
        //for now just CASH
        cout << "Payment Information : " << endl;
        cout << "Payment Method : Cash" << endl;      
        cout << "Payment status : Paid" << endl;
        cout << "-------------------------------------------------------------------------------------------------------------"<< endl;
        cout << "\t\t\t\t\tThank you for your purchase!\n\t\t\t\t\t\t Shop again" << endl;
        cout << "* For any inquiries, please contact our customer service at 123@example.com." << endl;
        cout << "* Return policy : Items can be returned within 30days of receipt." << endl;
}
bool Category::ChooseCategory(vector<Category>& categories, Cart& cart, Inventory& inventory, Checkout& check, Order& order, Customer& customer){
        int catnum;
        bool flag;
        while(1){        
            for(int i = 0 ; i < categories.size() ; i++){
                cout << i+1 <<". ";
                categories[i].display();
            }
            cout << "0. Checkout\n";                                                              
            cout << "Enter number : ";
            cin >> catnum;
            if(catnum == 0){
                system("cls");
                cout << "\nProceeding to checkout!" << endl;
                if(cart.get_Cartproducts().empty()){
                    return 0;
                }
                return check.checkout(cart,order,customer,inventory,check,categories);
            }
            if(catnum <= categories.size() && catnum > 0){
                break;
            }
            system("cls");
            cout << "You have entered incorrect Category number!\nPlease enter again" << endl;
            flag = false;
        }
        if(!categories[catnum-1].get_ProductsInCategory().empty()){
            cart.AddToCart(categories, catnum, inventory);
        }
        else{
            system("cls");
            cout << "There are no products to show in the chosen category!" << endl;
        }
        return 1;
}
void begin(){
     cout << "--------------------------------------------------------------------------------------\n"  
         << "--------------------------------------------------------------------------------------\n" 
         << "-------------------------Welcome to Online Shopping Store!----------------------------\n" 
         << "--------------------------------------------------------------------------------------\n" 
         << "--------------------------------------------------------------------------------------\n" << endl;
}

int main(){
    Customer c;
    Category cat;
    Product p;
    Cart cart;
    Inventory inventory;
    Checkout checkout;
    Order order;
    vector<Category> categories;
    cat.addDefaultCategories(categories);    
    cat.InitializeAllProducts(categories);
    Admin admin;
    //begin();
    inventory.set_InventoryCategories(categories);
    order.set_Tax(5);
    while(1){
        cart.get_Cartproducts().clear();
        cout << endl << endl;
        if(c.CheckLoginStatus(c,admin, inventory,categories,order)){
            inventory.set_InventoryCategories(categories);
            while(1){
                if(!cat.ChooseCategory(categories, cart, inventory, checkout, order ,c)){
                    if(cart.get_Cartproducts().empty()){
                        system("cls");
                        cout << "The cart is empty! nothing to checkout" << endl;
                        continue;
                    }
                    break;
                }
            }
        }
    }
    
}
