### Class Structure
#### Server Class
IRC Serverに関する包括的な情報を管理するクラス
```c++
	private:
		Command Class
		std::map<fd, User Class>
		std::vector<pollfd>
```

#### User Class
IRC Clientに関する包括的な情報を管理するクラス
```c++
	private:
		int fd
		std::string nick
		Message Class
```

#### Message Class
IRC Clientから受取った文字列情報を解析するクラス
```c++
	private:
		std::string msg_buf
```

#### Command Class
IRC Serverに実装するコマンド関数を集結させたクラス

#### Reply Hpp
IRC ServerがClientに投げるメッセージのマクロ一覧
